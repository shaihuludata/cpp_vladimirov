#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream>

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

    string (const string &s) {
        size = s.size;
        capacity = s.capacity;
        data = (char *)malloc(capacity);
        strncpy(data, s.data, size);
    }

    ~string () {
        free(data);
    }

    friend std::ostream& operator<<(std::ostream& os, const string s) {
        os << "my_string: " << s.data ;
        return os;
    }

    string operator=(const string & s) {
        free(data);
        size = s.size;
        capacity = s.capacity;
        data = (char *)malloc(capacity);
        strncpy(data, s.data, s.size);
        std::cerr << "not implemented yet" << std::endl;
        exit(1);
    }
};

/**
 * \section main.
 */
int main() {
    string s((char*)"Hello World!");
    string scopy(s);
    string s1((char *)"Other text");
    string s2 = s1;
    std::cout << s << std::endl;
    std::cout << scopy << std::endl;
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    return 0;
}
