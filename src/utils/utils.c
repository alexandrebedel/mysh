#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "utils.h"

char **split_by(char *line, const char *delimiters)
{
    char *copy = safe_strdup(line);
    char **args = NULL;
    char *token = strtok(copy, delimiters);
    int j = 0;

    while (token != NULL)
    {
        args = realloc(args, (j + 1) * sizeof(char *));
        args[j++] = safe_strdup(token);
        token = strtok(NULL, delimiters);
    }
    args = realloc(args, (j + 1) * sizeof(char *));
    args[j] = NULL;
    free(copy);
    return args;
}

bool display_prompt(void)
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

void display_char_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        printf("Element %d: [%s]\n", i, tab[i]);
}

int tab_len(void **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++)
        ;
    return i;
}
