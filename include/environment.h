#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include "minishell.h"

/**
 * Returns a newly allocated `char **`
 * from the provided env
 */
char **duplicate_env(char **env);

/**
 * Gets an environment variable by its name
 * and return the value
 *
 * WARN: Don't forget to free the value
 */
char *get_env_var(char **env, char *name);

/**
 * stdouts the provided env
 */
int dump_env(char **env);

/**
 * Mutates the given environment by the variable
 * name and the provided value
 *
 * @returns A success or failure code
 */
int set_env_var(char ***env, char *name, char *value);

/**
 * Removes from the given environment
 * the matching variable
 *
 * It will return a success code even
 * if the variable does not exist
 *
 * @returns A success or failure code
 */
int unset_env_var(char ***env, char *name);

#endif // ENVIRONMENT_H
