#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include "minishell.h"

/**
 * Gets an environment variable by its name
 * and return the value
 * 
 * WARN: Don't forget to free the value
 */
char *get_env_var(char **env, char *name);

#endif // ENVIRONMENT_H
