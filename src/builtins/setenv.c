#include "minishell.h"
#include <string.h>
#include "utils.h"
#include "environment.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

static bool is_str_alnum(char *str)
{
    bool is_alnum = true;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i]))
        {
            is_alnum = false;
        }
    }
    return is_alnum;
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
    int len = tab_len((void **)sh->args);

    if (len == 1)
        return 2;
    if (len > 3)
    {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return 1;
    }
    if (!isalpha(sh->args[1][0]))
    {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (!is_str_alnum(sh->args[1]))
    {
        fprintf(stderr, "setenv: Variable name must contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}

int sh_setenv(mysh_t *sh)
{
    int status = check_args(sh);

    if (status == 1)
        return 1;
    if (status == 2)
        return dump_env(sh->env);
    // char *line = get_env_var()
    // char **args = strip_by()
    // for (int i = 0; sh->env[i] != NULL; i++)
    // {
    //     if (strcmp(sh->env[i]))
    // }
    return 0;
}
