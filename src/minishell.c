#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "utils.h"
#include "builtins.h"

#if __linux__
#include <signal.h>
#endif

static const char *DELIMITERS = " \n\t";

int check_commands(mysh_t *sh)
{
    for (int i = 0; BUILTIN_COMMANDS[i] != NULL; i++)
    {
        if (strcmp(BUILTIN_COMMANDS[i], sh->args[0]) == 0)
            return BUILTIN_FNS[i](sh);
    }
    return processes_management(sh);
}

int init_shell(mysh_t *sh)
{
    char **args = NULL;
    size_t bufsize = 0;
    int ret_value = 0;

    signal(SIGINT, sigprompt);
    while (true)
    {
        if (isatty(0))
            display_prompt();
        if (getline(&sh->line, &bufsize, stdin) == -1)
            return ret_value;
        if (sh->line == NULL || strcmp(sh->line, "") == 0)
            continue;
        args = strip_by(sh->line, DELIMITERS);
        if (args[0] == NULL)
        {
            free_tab((void **)args);
            continue;
        }
        sh->args = args;
        ret_value = check_commands(sh);
        free_tab((void **)args);
    }
    return ret_value;
}