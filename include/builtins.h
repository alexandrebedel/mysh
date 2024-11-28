#if !defined(BUILTINS_H)
#define BUILTINS_H

#include "minishell.h"

typedef int (*builtin_fns_t)(mysh_t *sh);

// static const char *BUILTIN_FLAGS[] = {">", "<", ">>", "<<", "|", ";"};
const char *BUILTIN_COMMANDS[] = {"cd", "setenv", "unsetenv", "env", "exit", NULL};
builtin_fns_t BUILTIN_FNS[] = {sh_cd, sh_setenv, sh_unsetenv, sh_env, sh_exit};

#endif // BUILTINS_H
