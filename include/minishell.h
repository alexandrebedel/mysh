#if !defined(MINISHELL_H)
#define MINISHELL_H

#include <stdlib.h>

typedef struct
{
    char *bin_name;
    /**
     * Holds all the environments variables
     *
     * WARN: Don't forget to free on exit
     */
    char **env;
    /**
     * Holds all the paths inside the PATH
     * environment variable
     *
     * WARN: Don't forget to free on exit
     */
    char **paths;
    char **args;
} mysh_t;

/**
 * Initializes the shell
 */
int init_shell(mysh_t *mysh);

int processes_management(mysh_t *sh);

// Shell builtin function definition
//
int sh_exit(mysh_t *sh);
int sh_cd(mysh_t *sh);
int sh_setenv(mysh_t *sh);
int sh_unsetenv(mysh_t *sh);
int sh_env(mysh_t *sh);

#endif // MINISHELL_H
