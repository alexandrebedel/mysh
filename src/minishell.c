#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "minishell.h"
#include <unistd.h>
#include "utils.h"

static const char *DELIMITERS = " \n\t";

static int run_commands(mysh_t *sh)
{
    if (access(sh->args[0], F_OK) == 0)
    {
        printf("Executing local command\n");
        execve(sh->args[0], sh->args, sh->env);
        return 0;
    }
    for (int i = 0; sh->paths[i] != NULL; i++)
    {
        size_t len = strlen(sh->paths[i]) + strlen(sh->args[0]) + 2;
        char full_path[len];

        snprintf(full_path, len, "%s/%s", sh->paths[i], sh->args[0]);
        if (access(full_path, F_OK) == 0)
        {
            execve(full_path, sh->args, sh->env);
            return 0;
        }
    }
    return 0;
}

static int processes_management(mysh_t *sh)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        run_commands(sh);
    }
    else
    {
        do
        {
            waitpid(pid, &status, WUNTRACED | WCONTINUED);
            // if (w == -1)
            // {
            //     perror("waitpid");
            //     exit(EXIT_FAILURE);
            // }
            if (WIFEXITED(status))
            {
                printf("terminé, code=%d\n", WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("tué par le signal %d\n", WTERMSIG(status));
            }
            else if (WIFSTOPPED(status))
            {
                printf("arrêté par le signal %d\n", WSTOPSIG(status));
            }
            else if (WIFCONTINUED(status))
            {
                printf("relancé\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 0;
}

int init_shell(mysh_t *sh)
{
    char *line = NULL;
    size_t bufsize = 0;

    signal(SIGINT, sigprompt);
    while (true)
    {
        display_prompt();
        if (getline(&line, &bufsize, stdin) == -1)
            return (84);
        char **args = strip_by(line, DELIMITERS);

        sh->args = args;
        if (strcmp(args[0], "exit") == 0)
            return 0;
        processes_management(sh);
        free_tab((void **)args);
    }
    return 0;
}