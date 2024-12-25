#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils/memory.h"
#include "utils/utils.h"
#include "minishell.h"
#include "environment.h"
#include "node.h"

static inline int find_predicate(void *_env, void *context)
{
    environment_t *env = _env;

    return strcmp(env->name, (char *)context) == 0;
}

void free_env(void *_env)
{
    environment_t *env = _env;

    free(env->name);
    if (env->value)
        free(env->value);
    free(env);
}

node_t *dupenv(char **env)
{
    node_t *head = NULL;
    environment_t *environment;
    int len;

    for (int i = 0; env[i] != NULL; i++)
    {
        char *value = strchr(env[i], '=');

        if (!value)
            continue;
        len = value - env[i];
        environment = safe_malloc(sizeof(environment_t));
        environment->name = safe_strndup(env[i], len);
        environment->value = safe_strdup(&value[1]);
        environment->is_local = false;
        head = push_node(head, environment, free_env);
    }
    return head;
}

int set_env_var(mysh_t *sh, char *name, char *value)
{
    node_t *found_node = find_node(sh->env, find_predicate, name);

    if (found_node)
    {
        environment_t *env = (environment_t *)found_node->data;
        free(env->value);
        env->value = safe_strdup(value);
    }
    else
    {
        environment_t *new_node_data = malloc(sizeof(environment_t));
        new_node_data->is_local = false;
        new_node_data->name = safe_strdup(name);
        new_node_data->value = safe_strdup(value);
        push_node(sh->env, new_node_data, free_env);
    }
    return BUILTIN_SUCCESS;
}

environment_t *get_env_node(mysh_t *sh, char *name)
{
    node_t *found_node = find_node(sh->env, find_predicate, name);
    environment_t *env;

    if (found_node == NULL)
        return NULL;
    env = found_node->data;
    return env ? env : NULL;
}

char *get_env_var(mysh_t *sh, char *name)
{
    environment_t *env = get_env_node(sh, name);

    return env && env->value ? env->value : NULL;
}

int unset_env_var(mysh_t *sh, char *name)
{
    sh->env = remove_node(sh->env, find_predicate, (void *)name);
    return BUILTIN_SUCCESS;
}

int dump_env(node_t *node)
{
    node_t *current = node;
    environment_t *env;

    while (current != NULL)
    {
        env = (environment_t *)current->data;
        if (env->is_local)
        {
            current = current->next;
            continue;
        }
        printf("%s=%s\n", env->name, env->value);
        current = current->next;
    }
    return BUILTIN_SUCCESS;
}

char *env_to_string(void *data)
{
    environment_t *env = (environment_t *)data;

    if (env->is_local)
        return NULL;
    size_t len = strlen(env->name) + strlen(env->value) + 2;
    char *result = safe_malloc(len);

    snprintf(result, len, "%s=%s", env->name, env->value);
    return result;
}
