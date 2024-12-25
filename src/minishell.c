#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "minishell.h"
#include "utils/memory.h"
#include "utils/utils.h"
#include "prompt.h"
#include "environment.h"

#if __linux__
#include <signal.h>
#endif

static const char *DELIMITERS = " \n\t";

char **eval_variables(mysh_t *sh, char **args)
{
    environment_t *env;
    char *new_value = NULL;

    for (int i = 0; args[i] != NULL; i++)
    {
        if (args[i][0] != '$')
            continue;
        env = get_env_node(sh, &(args[i])[1]);
        if (env == NULL || (!env->is_local && !env->value))
            continue;
        if (env->is_local && env->localfn)
            new_value = env->localfn(sh);
        else
            new_value = safe_strdup(env->value);
        if (new_value)
        {
            free(args[i]);
            args[i] = new_value;
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
    int pipes_ran = 0;

    sh->sep_commands = split_by(sh->line, ";");
    for (int i = 0; sh->sep_commands[i] != NULL; i++)
    {
        if ((pipes_ran = check_pipes(sh, sh->sep_commands[i])) != NOPIPES)
            ret = pipes_ran;
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
