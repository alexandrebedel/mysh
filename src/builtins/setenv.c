#include "minishell.h"
#include <string.h>
#include "utils/utils.h"
#include "environment.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

static bool is_str_alnum(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '_' && !isalnum(str[i]))
            return false;
    }
    return true;
}

/**
 * Checks the args for errors and return
 * a status to process
 *
 * 0 - OK
 * 1 - KO
 * 2 - Running without params
 */
static int check_args(mysh_t *sh)
{
    int len = tablen((void **)sh->args);

    if (len == 1)
        return 2;
    if (len > 3)
    {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return BUILTIN_FAILURE;
    }
    if (!isalpha(sh->args[1][0]))
    {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return BUILTIN_FAILURE;
    }
    if (!is_str_alnum(sh->args[1]))
    {
        fprintf(stderr, "setenv: Variable name must contain alphanumeric characters.\n");
        return BUILTIN_FAILURE;
    }
    return BUILTIN_SUCCESS;
}

int sh_setenv(mysh_t *sh)
{
    int status = check_args(sh);

    if (status == BUILTIN_FAILURE)
        return status;
    if (status == 2)
        return dump_env(sh->env);
    return set_env_var(&sh->env, sh->args[1], sh->args[2]);
}
