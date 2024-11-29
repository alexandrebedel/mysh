#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

int sh_exit(mysh_t *sh)
{
    free_tab((void **)sh->paths);
    free_tab((void **)sh->args);
    free_tab((void **)sh->env);
    free(sh->line);
    exit(0);
    return 0;
}
