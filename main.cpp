#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cassert>

/* задача:
 * написать функцию
 * int replace_all для std::string
 * что-то вроде шаблонизатора, получается
 *
 */
using namespace std;

int strlen(const char * a) {
    int l = 0;
    while(1) {
        if (*(a + l) == '\0') { return l; }
        else (l++);
    }
}

void strncpy(char * a, const char * b, int l) {
    for (int i=0; i<=l; i++) {
        if (a[i] == '\0') { return; }
        a[i] = b[i];
    }
}

/**
 * \brief I create string class here..
 * Lesson-1 class realisation (part-ly).
 * \details 1. need god (good) constructor.
 * \details 2. need copy operator (i.e. '=')
 * \details 3. need cat operator (i.e. '+')
 * \details N. Koro4e, tam eche mojno stolko dopisivat - mama ne goruj.
 * Ya lu4he gulat na ulitsu sey4as...
 * I novij urok uje.
 * Class name is GodString. Deal with it.
 */

 /***********************************************************
  * \section class GodString header.
 **********************************************************/
class GodString
{
public:
    GodString();
    GodString(const char* str);
    ~GodString();

    int getMaxLength();
    const char* getStdString();
    void add(const char* str);

    void operator=(const char* str);
    void operator+(const char* str);

private:
    /// \note 32 - is God number. Or somehow...
    /// \note +1 need to store '\0' 
    static const size_t MAX_QUANTITY = (32 + 1);

    char m_data[GodString::MAX_QUANTITY] = {0};
    int m_currentSize;
};

/***********************************************************
 * \section class GodString implementation.
 **********************************************************/
GodString::GodString()
    : m_currentSize(0)
{
    std::cout << "Luntik: I'm alive!" << std::endl;
    std::cout << "Luntik: Also, I'm empty!!!" << std::endl;
}

GodString::GodString(const char* str)
{
    std::cout << "Luntik: I'm alive!" << std::endl;
    int len = strlen(str);
    if (len > MAX_QUANTITY)
    {
        std::cout << "It's too long!" << std::endl;
        std::cout << "I've cut it to " << getMaxLength() - 1 << std::endl;
        len = MAX_QUANTITY;
    }

    strncpy(m_data, str, len);
    m_currentSize = len;
    std::cout << "Luntik: Also, I'm " << len << " meters long." << std::endl;
}

GodString::~GodString()
{
    std::cout << "Luntik (one of): I'm dead..." << std::endl;
}

int GodString::getMaxLength()
{
    return MAX_QUANTITY;
}

const char* GodString::getStdString()
{
    if (m_currentSize == 0)
        return nullptr;
    else
        return (const char*) m_data;
}

void GodString::add(const char* str)
{
    int len = strlen(str);

    // check len
    if (m_currentSize + len > getMaxLength())
    {
        len = getMaxLength() - m_currentSize;

        std::cout << "It's too long!" << std::endl;
        std::cout << "I've cut it to " << len - 1 << std::endl;
    }

    strncpy(&m_data[m_currentSize], str, len);
}

void GodString::operator=(const char* str)
{
    // rewrite string
    int len = strlen(str);
    if (len > MAX_QUANTITY)
    {
        std::cout << "It's too long!" << std::endl;
        std::cout << "I've cut it to " << getMaxLength() - 1 << std::endl;
        len = MAX_QUANTITY;
    }

    strncpy(m_data, str, len);
    m_currentSize = len;
    std::cout << "Luntik: Also, I'm " << len << " meters long." << std::endl;
}

void GodString::operator+(const char* str)
{
    add(str);
}

/**
 * \section module other prototypes.
 */
int replace_all(string& str, string& from, string& to);

/**
 * \section module other implementations.
 */
int replace_all(string& str, string& from, string& to) {
    int nrepl = 0;
    std::size_t npos;
    while ((npos = str.find(from)) != std::string::npos) {
        str.replace(npos, from.length(), to);
        nrepl++;
    }
    return nrepl;
};

void Test1()
{
    string str("Hello %username! How are you doing, %username?");
    std::cout << str << std::endl;
    string from("%username");
    string to("Denis, the Toxic");
    int nrepl = replace_all(str, from, to);
    std::cout << str << std::endl;
    assert(nrepl == 2);
}

void Test2()
{
    // Stage 1. Create in various ways.
    GodString empty_str;
    GodString aaaa_str("aaaa");
    GodString bb_str("bb");

    // Stage 2. Add() method. 
    std::cout << "I'll add to \"" << aaaa_str.getStdString() <<
        "\" str \"" << bb_str.getStdString() << "\" str" << std::endl;

    aaaa_str.add(bb_str.getStdString());
    std::cout << "Result is: " << aaaa_str.getStdString() << std::endl;
    std::cout << "//note: It's magic, magic!!!!" << std::endl;
    std::cout << std::endl;

    // Stage 3. Operators magic.   
    std::cout << "create siberia string" << std::endl;
    GodString siberia_str = "siberia";
    std::cout << "Siberia body is: " << siberia_str.getStdString() << std::endl;
    std::cout << "//note: It's magic, magic!!!!" << std::endl;
    std::cout << std::endl;

    GodString sogood_str = " so good!";
    std::cout << "I'll do \"" << siberia_str.getStdString() <<
        "\" + \"" << sogood_str.getStdString() << "\" str" << std::endl;

    siberia_str + sogood_str.getStdString();

    std::cout << "Result is: " << siberia_str.getStdString() << std::endl;
    std::cout << "//note: It's magic, magic!!!!" << std::endl;
}

/***********************************************************
 * \section main.
 **********************************************************/
int main() {
    std::cout << "start test-1: replace_all()" << std::endl;
    Test1();
    std::cout << std::endl << std::endl;

    std::cout << "start test-2: string class" << std::endl;
    Test2();
    std::cout << std::endl << std::endl;

    return 0;
}


