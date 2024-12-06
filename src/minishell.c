#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"
#include "utils.h"
#include "builtins.h"
#include "environment.h"

#if __linux__
#include <signal.h>
#endif

static const char *DELIMITERS = " \n\t";

int check_commands(mysh_t *sh)
{
    for (int i = 0; BUILTIN_COMMANDS[i] != NULL; i++)
    {
        if (strcmp(BUILTIN_COMMANDS[i], sh->args[0]) == 0)
            return BUILTIN_FNS[i](sh);
    }
    return processes_management(sh);
}

/**
 * Checks for arguments starting with `$` in the command line
 * and replaces them with their environment variable values.
 */
char **eval_variables(mysh_t *sh, char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] == '$' && isalnum(args[i][1]))
        {
            char *value = get_env_var(sh->env, &(args[i])[1]);

            // TODO: Should we return an error message when
            // the variable is not found?
            if (value == NULL)
                return args;
            free(args[i]);
            args[i] = value;
        }
    }
    return args;
}

/**
 * Splits the input line by `;` and processes each command.
 */
int check_separators(mysh_t *sh)
{
    char **args = NULL;
    int ret = 0;

    sh->sep_commands = split_by(sh->line, ";");
    for (int i = 0; sh->sep_commands[i] != NULL; i++)
    {
        if (check_pipes(sh, sh->sep_commands[i]) != NOPIPES)
        {
        }
        else
        {
            args = split_by(sh->sep_commands[i], DELIMITERS);
            if (args[0] == NULL)
            {
                freetab((void **)args);
                continue;
            }
            sh->args = eval_variables(sh, args);
            ret = check_commands(sh);
            freetab((void **)args);
        }
        // check_pipes(sh, sh->sep_commands[i]);
    }
    freetab((void **)sh->sep_commands);
    return ret;
}

int run_shell(mysh_t *sh)
{
    size_t bufsize = 0;
    int ret_value = 0;

    signal(SIGINT, sigprompt);
    while (true)
    {
        if (isatty(0))
            display_prompt();
        if (getline(&sh->line, &bufsize, stdin) == -1)
            return EXIT_FAILURE;
        if (sh->line == NULL || strcmp(sh->line, "") == 0)
            continue;
        ret_value = check_separators(sh);
    }
    return ret_value;
}