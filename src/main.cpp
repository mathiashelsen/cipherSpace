#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "string2hex.hpp"
#include "aes.hpp"

using namespace std;

int main(int argc, char **argv)
{
    int i = 0;
    aes aesCipher;
    aesCipher.setKey(hex_to_bin(std::string("000102030405060708090A0B0C0D0E0F"), &i));
    //aesCipher.setKey(hex_to_bin(std::string("00000000000000000000000000000000"), &i));
    cout << aesCipher.printKey() << endl;
    cout << aesCipher.printRoundKeys() << endl;
    return(0);
}

/*

string hello = "hello world!";

cout << hello << endl << string_to_hex(hello) << endl;

const char * cstring = hello.c_str();
for(int i = 0; i < hello.length(); i++)
{
    printf("%d ", cstring[i]);
}
printf("\n");
)
int i = 0;
char *tmp = hex_to_bin(string_to_hex(hello), &i);

for(int j = 0; i < i; j++)
{
    printf("%d ", tmp[i]);
}
printf("\n");
free(tmp);
*/
