#if !defined(MINISHELL_H)
#define MINISHELL_H

#include "node.h"
#include <stdlib.h>
#include <stdbool.h>

#define SIGNAL_EXIT(sigvalue) (128 + sigvalue)

#define BUILTIN_SUCCESS 0
#define BUILTIN_FAILURE 1

#define NOPIPES -1

typedef struct
{
    char *line;
    /**
     * Holds the environment using the environment_t struct
     *
     * Needs to be free'd
     */
    node_t *env;
    char **args;
    /**
     * Hold the commands separated by `;`
     */
    char **sep_commands;
    /**
     * Last command exit status
     */
    int exit_status;
    pid_t current_pid;
} mysh_t;

/**
 * Initializes the shell
 */
int run_shell(mysh_t *mysh);

mysh_t init_struct(char **env);

// Shell builtin function definition
//
int sh_exit(mysh_t *sh);
int sh_cd(mysh_t *sh);
int sh_setenv(mysh_t *sh);
int sh_unsetenv(mysh_t *sh);
int sh_env(mysh_t *sh);

/**
 * Checks for arguments starting with `$` in the command line
 * and replaces them with their environment variable values.
 */
char **eval_variables(mysh_t *sh, char **args);

int check_separators(mysh_t *sh);

// Shell commands functions definition
//
/**
 * Checks for builtins and sets the
 * last shell exit_status code
 */
int check_commands(mysh_t *sh);
int processes_management(mysh_t *sh);

/**
 * Evaluates the pipes from the provided
 * CL and sets the last shell exit_status code
 */
int check_pipes(mysh_t *sh, char *line);

#endif // MINISHELL_H
