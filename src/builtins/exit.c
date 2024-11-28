#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

int sh_exit(mysh_t *sh)
{
    free_tab(sh->paths);
    free_tab(sh->args);
    exit(0);
    return 0;
}
