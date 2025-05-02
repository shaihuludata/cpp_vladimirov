#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <errno.h>

using namespace std;

int f ();

int main()
{
    char * r;

    cout << "Hello World!" << endl;
    char a[] = "auto_b=auti";
    auto b = strtok_r(a, "=", &r);
    cout << b << endl;
    cout << r << endl;

    f();
    return 0;
}

int f ()
{
  FILE * pFile;
  pFile = fopen ("unexist.ent","r");
  if (pFile == NULL)
    printf ("Error opening file unexist.ent: %s\n",strerror(errno));
  return 0;
}
