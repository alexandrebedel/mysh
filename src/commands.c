#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include <unistd.h>
#include <string.h>

#if __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

static int run_commands(mysh_t *sh)
{
    if (access(sh->args[0], F_OK) == 0)
    {
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
    fprintf(stderr, "%s: Command not found.\n", sh->args[0]);
    return 1;
}

static int waitprocess(pid_t pid)
{
    int ret = 0;
    int status = 0;

    do
    {
        waitpid(pid, &status, WUNTRACED | WCONTINUED);
        if (WIFEXITED(status))
            ret = WEXITSTATUS(status);
        if (WTERMSIG(status) == SIGSEGV)
        {
            fprintf(stderr, "Segmentation fault\n");
            ret = 139;
        }
        else if (WTERMSIG(status) == SIGFPE)
        {
            fprintf(stderr, "Floating exception\n");
            ret = 136;
        }
        // else if (WIFSIGNALED(status))
        // {
        //     printf("tué par le signal %d\n", WTERMSIG(status));
        // }
        // else if (WIFSTOPPED(status))
        // {
        //     printf("arrêté par le signal %d\n", WSTOPSIG(status));
        // }
        // else if (WIFCONTINUED(status))
        // {
        //     printf("relancé\n");
        // }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ret;
}

int processes_management(mysh_t *sh)
{
    pid_t pid = fork();
    int status = 0;
    int ret = 0;

    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
        ret = run_commands(sh);
    else
        ret = waitprocess(pid);
    return ret;
}
