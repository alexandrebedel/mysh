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
    char old_pwd[FILENAME_MAX];
    char *home = get_env_var(sh->env, "HOME");
    int ret = BUILTIN_SUCCESS;

    if (getcwd(old_pwd, FILENAME_MAX) == NULL)
        return BUILTIN_FAILURE;
    if (!home)
        return BUILTIN_FAILURE;
    if (chdir(home) == 0)
    {
        set_env_var(&sh->env, "PWD", home);
        set_env_var(&sh->env, "OLDPWD", old_pwd);
    }
    else
    {
        fprintf(stderr, "%s: %s\n", home, strerror(errno));
        ret = BUILTIN_FAILURE;
    }
    free(home);
    return ret;
}

static int move_to(mysh_t *sh, char *directory)
{
    char cwd[FILENAME_MAX];
    char new_cwd[FILENAME_MAX];

    if (getcwd(cwd, FILENAME_MAX) == NULL)
        return BUILTIN_FAILURE;
    if (chdir(directory) == -1)
    {
        fprintf(stderr, "%s: %s.\n", directory, strerror(errno));
        return BUILTIN_FAILURE;
    }
    if (getcwd(new_cwd, FILENAME_MAX) == NULL)
        return BUILTIN_FAILURE;
    set_env_var(&sh->env, "PWD", new_cwd);
    set_env_var(&sh->env, "OLDPWD", cwd);
    return BUILTIN_SUCCESS;
}

int sh_cd(mysh_t *sh)
{
    int size = tab_len((void **)sh->args);
    int ret = 0;

    if (size > 3)
    {
        fprintf(stderr, "cd: Too many arguments.\n");
        return BUILTIN_FAILURE;
    }
    if (size == 1 || sh->args[1][0] == '~')
        return move_home(sh);
    else if (sh->args[1][0] == '-')
    {
        char *path = get_env_var(sh->env, "OLDPWD");

        if (path == NULL)
            return BUILTIN_FAILURE;
        ret = move_to(sh, path);
        free(path);
    }
    else
        ret = move_to(sh, sh->args[1]);
    return ret;
}
