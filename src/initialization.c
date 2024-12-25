#include <unistd.h>
#include <stdio.h>
#include "utils/utils.h"
#include "utils/memory.h"
#include "minishell.h"
#include "environment.h"

static char *get_last_exit_code(mysh_t *sh)
{
    char *value = safe_malloc(4);

    if (snprintf(value, 4, "%d", sh->exit_status) < 0)
    {
        free(value);
        return NULL;
    }
    return value;
}

static char *get_current_pid(mysh_t *sh)
{
    char *value = safe_malloc(6);

    if (snprintf(value, 6, "%d", sh->current_pid) < 0)
    {
        free(value);
        return NULL;
    }
    return value;
}

// TODO: Improve this with struct function builders
static void init_local_vars(mysh_t *sh)
{
    environment_t *exit_code = malloc(sizeof(environment_t));
    environment_t *current_pid = malloc(sizeof(environment_t));

    exit_code->is_local = true;
    exit_code->name = safe_strdup("?");
    exit_code->value = NULL;
    exit_code->localfn = get_last_exit_code;
    //
    current_pid->is_local = true;
    current_pid->name = safe_strdup("$");
    current_pid->value = NULL;
    current_pid->localfn = get_current_pid;
    push_node(sh->env, exit_code, free_env);
    push_node(sh->env, current_pid, free_env);
}

mysh_t init_struct(char **env)
{
    mysh_t sh;

    sh.current_pid = getpid();
    sh.env = dupenv(env);
    sh.line = NULL;
    sh.exit_status = 0;
    init_local_vars(&sh);
    return sh;
}
