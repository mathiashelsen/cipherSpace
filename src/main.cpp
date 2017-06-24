#include <iostream>
#include "util/serverSide.hpp"

void printText(char *input, char **output);

int main(void)
{
    serverSide myServer = serverSide(1025, &printText);
    return(0);
}

void printText(char *input, char **output)
{
    printf("Received the following message:\n\t%s", input);
    printf("\nEnd-of-message\n");
}
