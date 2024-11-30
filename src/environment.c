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
    char **copy = safe_malloc(sizeof(char *) * (tablen((void **)env) + 1));
    int i = 0;

    for (; env[i] != NULL; i++)
        copy[i] = safe_strdup(env[i]);
    copy[i] = NULL;
    return copy;
}

char *get_env_var(char **env, char *name)
{
    char *ret = NULL;

    for (int i = 0; env[i] != NULL; i++)
    {
        char **env_var = split_by(env[i], "=");

        if (strcmp(env_var[0], name) == 0)
            ret = safe_strdup(env_var[1]);
        freetab((void **)env_var);
    }
    return ret;
}

int set_env_var(char ***env, char *name, char *value)
{
    int size = tablen((void **)*env);
    char *new_var = safe_malloc(sizeof(char) * (strlen(name) + strlen(value ? value : "") + 2));
    char **copy;

    if (!new_var)
        return BUILTIN_FAILURE;
    sprintf(new_var, "%s=%s", name, value ? value : "");
    for (int i = 0; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], name, strlen(name)) == 0 && (*env)[i][strlen(name)] == '=')
        {
            free((*env)[i]);
            (*env)[i] = new_var;
            return BUILTIN_SUCCESS;
        }
    }
    copy = realloc(*env, sizeof(char *) * (size + 2));
    if (!copy)
    {
        free(new_var);
        return BUILTIN_FAILURE;
    }
    *env = copy;
    (*env)[size] = new_var;
    (*env)[size + 1] = NULL;
    return BUILTIN_SUCCESS;
}

int unset_env_var(char ***env, char *name)
{
    int i = 0;
    int j = 0;
    char **copy;

    if (!var_exists(*env, name))
        return BUILTIN_SUCCESS;
    copy = safe_malloc(sizeof(char *) * tablen((void **)*env));
    for (; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], name, strlen(name)) == 0 && (*env)[i][strlen(name)] == '=')
            continue;
        copy[j++] = safe_strdup((*env)[i]);
    }
    copy[j] = NULL;
    freetab((void **)*env);
    *env = copy;
    return BUILTIN_SUCCESS;
}

int dump_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
    {
        printf("%s\n", env[i]);
    }
    return BUILTIN_SUCCESS;
}