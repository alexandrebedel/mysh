#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"

int sh_unsetenv(mysh_t *sh)
{
    int size = tab_len((void **)sh->args);

    if (size == 1)
    {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return BUILTIN_FAILURE;
    }
    for (int i = 1; sh->args[i] != NULL; i++)
    {
        if (unset_env_var(&sh->env, sh->args[i]) == 1)
            return BUILTIN_FAILURE;
    }
    return BUILTIN_SUCCESS;
}
