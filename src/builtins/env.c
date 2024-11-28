#include <stdio.h>
#include "minishell.h"
#include "environment.h"

int sh_env(mysh_t *sh)
{
    return dump_env(sh->env);
}
