#include "minishell.h"
#include "utils/memory.h"
#include <stdlib.h>

int sh_exit(mysh_t *sh)
{
    free_shell(sh);
    exit(0);
    return 0;
}
