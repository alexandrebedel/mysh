#if !defined(MEMORY_H)
#define MEMORY_H

#include "minishell.h"

/**
 * Exits the program and display the error on stderr
 */
void free_shell(mysh_t *sh);

/**
 * Displays a memory error and exits
 */
void memory_error(void);

void *safe_malloc(size_t size);

char *safe_strdup(const char *str);

/**
 * Frees a 2d array
 */
void freetab(void **tab);

#endif // MEMORY_H
