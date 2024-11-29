#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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

void free_tab(void **tab)
{
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}
