#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "utils/memory.h"
#include "environment.h"

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

void display_char_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        printf("Element %d: [%s]\n", i, tab[i]);
}

int tablen(void **tab)
{
    int i = 0;

    for (; tab[i] != NULL; i++)
        ;
    return i;
}
