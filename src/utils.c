#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "utils.h"

char **strip_by(char *line, const char *delimiters)
{
    char *copy = strdup(line);
    char **args = NULL;
    char *token = strtok(copy, delimiters);
    int j = 0;

    while (token != NULL)
    {
        args = realloc(args, (j + 1) * sizeof(char *));
        args[j++] = strdup(token);
        token = strtok(NULL, delimiters);
    }
    args = realloc(args, (j + 1) * sizeof(char *));
    args[j] = NULL;
    free(copy);
    return args;
}

bool display_prompt(void)
{
    int bytes = write(STDOUT_FILENO, "> ", 2);

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

void free_tab(void **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}