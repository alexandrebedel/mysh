#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils.h"
#include "environment.h"
#include <unistd.h>
#include <string.h>

#if __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define LOCAL_BIN 2
#define PATH_BIN 1
#define NOTFND_BIN 0

static int get_bin_type(mysh_t *sh)
{
    if (access(sh->args[0], X_OK) == 0)
        return LOCAL_BIN;
    for (int i = 0; sh->paths[i] != NULL; i++)
    {
        size_t len = strlen(sh->paths[i]) + strlen(sh->args[0]) + 2;
        char full_path[len];

        snprintf(full_path, len, "%s/%s", sh->paths[i], sh->args[0]);
        if (access(full_path, X_OK) == 0)
            return PATH_BIN;
    }
    return NOTFND_BIN;
}

static void run_command(mysh_t *sh, int command_status)
{
    if (command_status == LOCAL_BIN)
    {
        execve(sh->args[0], sh->args, sh->env);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; sh->paths[i] != NULL; i++)
    {
        size_t len = strlen(sh->paths[i]) + strlen(sh->args[0]) + 2;
        char full_path[len];

        snprintf(full_path, len, "%s/%s", sh->paths[i], sh->args[0]);
        execve(full_path, sh->args, sh->env);
    }
    perror("execve");
    exit(EXIT_FAILURE);
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
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ret;
}

int processes_management(mysh_t *sh)
{
    int ret = 0;
    int status = 0;
    pid_t pid;

    // get_paths_from_env(sh);
    // TODO: "Exec format error. Wrong Architecture."
    if ((status = get_bin_type(sh)) == 0)
    {
        fprintf(stderr, "%s: Command not found.\n", sh->args[0]);
        return EXIT_FAILURE;
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
        run_command(sh, status);
    else
        ret = waitprocess(pid);
    return ret;
}
