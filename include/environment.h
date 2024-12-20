#if !defined(ENVIRONMENT_H)
#define ENVIRONMENT_H

#include "minishell.h"

typedef struct
{
    char *name;
    char *value;
    bool is_local;
} environment_t;

/**
 * Saves the environment into a `node_t<environment_t>` linked list
 */
node_t *dupenv(char **env);

/**
 * Looks inside the `node_t<environment_t>` and return
 * the matching value. No need to free since it will
 * be done by the free_node function
 */
char *get_env_var(mysh_t *sh, char *name);

/**
 * stdouts the provided env
 */
int dump_env(node_t *env);

/**
 * Mutates the given environment by the variable
 * name and the provided value
 *
 * @returns A success or failure code
 */
int set_env_var(mysh_t *sh, char *name, char *value);

/**
 * Removes from the given environment
 * the matching variable
 *
 * It will return a success code even
 * if the variable does not exist
 *
 * @returns A success or failure code
 */
int unset_env_var(mysh_t *sh, char *name);

/**
 * Mapper function to transform the node_t<environment_t> to a char **
 */
char *env_to_string(void *data);

#endif // ENVIRONMENT_H
