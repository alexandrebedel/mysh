#if !defined(MINISHELL_H)
#define MINISHELL_H

#include <stdlib.h>

#define BUILTIN_SUCCESS 0
#define BUILTIN_FAILURE 1

#define NOPIPES -1

typedef struct
{
    char *bin_name;
    char *line;
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
    /**
     * TODO: documentation
     */
    char **sep_commands;
} mysh_t;

/**
 * Initializes the shell
 */
int run_shell(mysh_t *mysh);

int processes_management(mysh_t *sh);

// Shell builtin function definition
//
int sh_exit(mysh_t *sh);
int sh_cd(mysh_t *sh);
int sh_setenv(mysh_t *sh);
int sh_unsetenv(mysh_t *sh);
int sh_env(mysh_t *sh);

char **eval_variables(mysh_t *sh, char **args);
int check_separators(mysh_t *sh);
int check_commands(mysh_t *sh);

// Pipes related functions
int check_pipes(mysh_t *sh, char *line);

#endif // MINISHELL_H
