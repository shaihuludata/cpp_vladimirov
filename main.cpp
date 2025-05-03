#include <iostream>
#include <cassert>

/* задача:
 * написать функцию
 * int replace_all для std::string
 * что-то вроде шаблонизатора, получается
 *
 */
using namespace std;

int replace_all(string & str, string & from, string & to);

/**
 * \section main.
 */
int main() {
    string str("Hello %username! How are you doing, %username?");
    std::cout << str << std::endl;
    string from("%username");
    string to("Denis, the Toxic");
    int nrepl = replace_all(str, from, to);
    std::cout << str << std::endl;
    assert(nrepl == 2);
    return 0;
}

int replace_all(string & str, string & from, string & to) {
    int nrepl = 0;
    std::size_t npos;
    while ((npos = str.find(from)) != std::string::npos) {
        str.replace(npos, from.length(), to);
        nrepl++;
    }
    return nrepl;
};
