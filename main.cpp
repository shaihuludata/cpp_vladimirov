#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

//using namespace std;

class string {
    char * data;
    size_t size;
    size_t capacity;
public:

    string (char * s) {
        size = strlen(s);
        capacity = size + 10;
        data = (char *)malloc(capacity);
        strncpy(data, s, size);
    }

    ~string () {
//        free(data);
    }

    friend std::ostream& operator<<(std::ostream& os, const string s) {
        os << "my_string: " << s.data ;
        return os;
    }
    // TODO copy assignment
//    const string operator=() {
//
//    }
};

int main()
{
    string s((char*)"Hello World!");
//    string scopy(s);
//    string s1("Other text");
//    s1 = s;
    std::cout << s << std::endl;

    return 0;
}
