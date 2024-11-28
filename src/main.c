#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"

static mysh_t init_struct(char **env)
{
    char *path = get_env_var(env, "PATH");
    mysh_t sh;

    if (path == NULL)
        path = strdup("/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin");
    sh.paths = strip_by(path, ":");
    sh.env = env;
    free(path);
    return sh;
}

int main(int argc, char *argv[], char **env)
{
    mysh_t mysh = init_struct(env);
    (void)argc;

    // // free_tab(mysh.paths);
    mysh.bin_name = argv[0];
    return init_shell(&mysh);
}