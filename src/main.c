#include "minishell.h"
#include "utils/memory.h"

static void free_all(mysh_t sh)
{
    free_nodes(sh.env);
    free(sh.line);
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
