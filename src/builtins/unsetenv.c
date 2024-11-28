#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"

int sh_unsetenv(mysh_t *sh)
{
    int size = tab_len(sh->env);

    if (size == 1)
    {
        fprintf(stderr, "unsetenv: Too few arguments..\n");
        return 1;
    }
    for (int i = 1; sh->args[i] != NULL; i++)
    {
        if (unset_env_var(&sh->env, sh->args[i]) == 1)
            return 1;
    }
    return 0;
}
