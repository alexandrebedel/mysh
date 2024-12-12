#if !defined(PROMPT_H)
#define PROMPT_H

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

#endif // PROMPT_H
