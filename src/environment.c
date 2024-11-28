#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "minishell.h"
#include "environment.h"
#include <string.h>

static bool var_exists(char **env, char *name)
{
    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], name, strlen(name)) == 0)
            return true;
    }
    return false;
}

char **duplicate_env(char **env)
{
    char **copy = malloc(sizeof(char *) * (tab_len((void **)env) + 1));
    int i = 0;

    for (; env[i] != NULL; i++)
        copy[i] = strdup(env[i]);
    copy[i] = NULL;
    return copy;
}

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
        free_tab((void **)env_var);
    }
    return ret;
}

int set_env_var(char ***env, char *name, char *value)
{
    int size = tab_len((void **)*env);
    char *new_var = malloc(sizeof(char) * (strlen(name) + strlen(value) + 2));
    char **copy;

    if (!new_var)
        return 1;
    sprintf(new_var, "%s=%s", name, value);
    for (int i = 0; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], name, strlen(name)) == 0 && (*env)[i][strlen(name)] == '=')
        {
            free((*env)[i]);
            (*env)[i] = new_var;
            return 0;
        }
    }
    copy = realloc(*env, sizeof(char *) * (size + 2));
    if (!copy)
    {
        free(new_var);
        return 1;
    }
    *env = copy;
    (*env)[size] = new_var;
    (*env)[size + 1] = NULL;
    return 0;
}

int unset_env_var(char ***env, char *name)
{
    int i = 0;
    int j = 0;
    char **copy;

    if (!var_exists(*env, name))
        return 0;
    copy = malloc(sizeof(char *) * tab_len((void **)*env));
    for (; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], name, strlen(name)) == 0 && (*env)[i][strlen(name)] == '=')
            continue;
        copy[j++] = strdup((*env)[i]);
    }
    copy[j] = NULL;
    free_tab(*env);
    *env = copy;
    return 0;
}

int dump_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
    {
        printf("%s\n", env[i]);
    }
    return 0;
}