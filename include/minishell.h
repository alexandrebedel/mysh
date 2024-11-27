#if !defined(MINISHELL_H)
#define MINISHELL_H

static const char *BUILTIN_FLAGS[] = {">", "<", ">>", "<<", "|", ";"};

typedef struct
{
    /**
     * Holds all the environments variables
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

#endif // MINISHELL_H
