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

static int check_commands(mysh_t *sh)
{
    for (int i = 0; BUILTIN_COMMANDS[i] != NULL; i++)
    {
        if (strcmp(BUILTIN_COMMANDS[i], sh->args[0]) == 0)
            return BUILTIN_FNS[i](sh);
    }
    return processes_management(sh);
}

static int check_separators(mysh_t *sh)
{
    char **args = NULL;
    int ret = 0;

    sh->sep_commands = split_by(sh->line, ";");
    for (int i = 0; sh->sep_commands[i] != NULL; i++)
    {
        args = split_by(sh->sep_commands[i], DELIMITERS);
        if (args[0] == NULL)
        {
            free_tab((void **)args);
            continue;
        }
        sh->args = args;
        ret = check_commands(sh);
        free_tab((void **)args);
    }
    free_tab((void **)sh->sep_commands);
    return ret;
}

int run_shell(mysh_t *sh)
{
    size_t bufsize = 0;
    int ret_value = 0;

    signal(SIGINT, sigprompt);
    while (true)
    {
        if (isatty(0))
            display_prompt();
        if (getline(&sh->line, &bufsize, stdin) == -1)
            return EXIT_FAILURE;
        if (sh->line == NULL || strcmp(sh->line, "") == 0)
            continue;
        ret_value = check_separators(sh);
    }
    return ret_value;
}