#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "minishell.h"
#include "environment.h"
#include <strings.h>

char *get_env_var(char **env, char *name)
{
    char *ret = NULL;

    for (int i = 0; env[i] != NULL; i++)
    {
        char **env_var = strip_by(env[i], "=");

        if (strcmp(env_var[0], name) == 0)
        {
            ret = strdup(env_var[1]);
        }
        free_tab(env_var);
    }
    return ret;
}