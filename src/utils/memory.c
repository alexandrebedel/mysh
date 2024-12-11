#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "minishell.h"

void free_shell(mysh_t *sh)
{
    freetab((void **)sh->paths);
    freetab((void **)sh->args);
    freetab((void **)sh->env);
    freetab((void **)sh->sep_commands);
    if (sh->line)
        free(sh->line);
}

void memory_error(void)
{
    fprintf(stderr, "critical error: Out of memory\n");
    exit(EXIT_FAILURE);
}

char *safe_strdup(const char *str)
{
    char *ptr = strdup(str);

    if (ptr == NULL)
        memory_error();
    return ptr;
}

void *safe_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        memory_error();
    return ptr;
}

void freetab(void **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
    {
        if (tab[i] != NULL)
            free(tab[i]);
    }
    free(tab);
}
