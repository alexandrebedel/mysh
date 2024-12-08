#if !defined(UTILS_H)
#define UTILS_H

#include "minishell.h"
#include <stdbool.h>

/**
 * Displays the prompt and return a boolean
 * value if the write syscall fails
 */
bool display_prompt(void);

/**
 * Used to deal with the SIGINT signal
 *
 * CTRL + C
 */
void sigprompt(__attribute__((__unused__)) int sig);

/**
 * Util function to display a
 * two dimensionnal char array
 */
void display_char_tab(char **tab);

/**
 * Returns a `char **` of the parsed line
 * matching the given delimiter.
 */
char **split_by(char *line, const char *delimiters);

/**
 * Returns the size of a 2d array
 */
int tablen(void **tab);

// Memory related functions
//

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

#endif // UTILS_H
