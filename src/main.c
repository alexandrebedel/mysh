#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "utils/utils.h"
#include "utils/memory.h"
#include "environment.h"

static void free_all(mysh_t sh)
{
    freetab((void **)sh.paths);
    free_nodes(sh.env);
    free(sh.line);
}

// static int init_local_vars()
// {
//     environment_t *exit_code = { .name = safe_strdup("$") }
// }

static mysh_t init_struct(char **env)
{
    mysh_t sh;

    // Should the paths be handled by the PATH variable itself ?
    sh.env = dupenv(env);
    sh.paths = split_by(get_env_var(&sh, "PATH"), ":");
    sh.line = NULL;
    sh.exit_status = 0;
    return sh;
}

int main(int argc, char *argv[], char *env[])
{
    int ret = 0;
    mysh_t mysh = init_struct(env);
    (void)argc, (void)argv;

    ret = run_shell(&mysh);
    free_all(mysh);
    return ret;
}
