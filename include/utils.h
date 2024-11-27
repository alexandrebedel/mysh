#if !defined(UTILS_H)
#define UTILS_H

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
 *
 * TODO: Error handling
 */
char **strip_by(char *line, const char *delimiters);

/**
 * Returns the size of a 2d array
 */
int two_d_size(void **tab);

/**
 * Frees a 2d array
 */
void free_tab(void **tab);

#endif // UTILS_H
