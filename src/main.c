#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"

static void free_all(mysh_t sh)
{
    free_tab((void **)sh.paths);
    free_tab((void **)sh.env);
    free(sh.line);
}

static mysh_t init_struct(char **env)
{
    char *path = get_env_var(env, "PATH");
    mysh_t sh;

    // Should the paths be handled by the PATH variable itself ?
    sh.paths = split_by(path, ":");
    sh.env = duplicate_env(env);
    sh.line = NULL;
    free(path);
    return sh;
}

int main(int argc, char *argv[], char **env)
{
    int ret = 0;
    mysh_t mysh = init_struct(env);
    (void)argc;

    mysh.bin_name = argv[0];
    ret = run_shell(&mysh);
    free_all(mysh);
    return ret;
}