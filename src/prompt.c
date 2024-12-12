#include <unistd.h>
#include <stdio.h>
#include "prompt.h"

bool display_prompt()
{
    char pwd[256];
    int bytes = dprintf(STDOUT_FILENO, "\033[1m[\033[0m\033[35m%s\033[0m\033[1m]> \033[0m", getcwd(pwd, sizeof(pwd)));

    return !(bytes == -1);
}

void sigprompt(__attribute__((__unused__)) int sig)
{
    printf("\n");
    display_prompt();
}