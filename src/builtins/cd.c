#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"

#if __linux__
#include <sys/types.h>
#endif

static int move_home(mysh_t *sh)
{
    char *home = get_env_var(sh->env, "HOME");
    int ret = BUILTIN_SUCCESS;

    if (!home)
        return BUILTIN_FAILURE;
    if (chdir(home) == 0)
        set_env_var(&sh->env, "PWD", home);
    else
    {
        fprintf(stderr, "%s: %s\n", home, strerror(errno));
        ret = BUILTIN_FAILURE;
    }
    free(home);
    return ret;
}

static int move_to(char *directory)
{
    if (chdir(directory) == -1)
    {
        perror("mycd");
        return 1;
    }
    printf("moved to directory\n");
}

int sh_cd(mysh_t *sh)
{
    int size = tab_len((void **)sh->args);

    if (size > 3)
    {
        fprintf(stderr, "cd: Too many arguments.\n");
        return BUILTIN_FAILURE;
    }
    if (size == 1 || sh->args[1][0] == '~')
        move_home(sh);
    else
    {
    }
    return 0;
}
