#if !defined(UTILS_H)
#define UTILS_H

#include "minishell.h"

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

#endif // UTILS_H
