#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils/memory.h"
#include "utils/utils.h"
#include "environment.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "builtins.h"

#if __linux__
#include <sys/types.h>
#include <sys/wait.h>
#endif

#define LOCAL_BIN 2
#define PATH_BIN 1
#define NOTFND_BIN 0

static int get_bin_type(mysh_t *sh, char **paths)
{
    if (access(sh->args[0], X_OK) == 0)
        return LOCAL_BIN;
    for (int i = 0; paths && paths[i] != NULL; i++)
    {
        size_t len = strlen(paths[i]) + strlen(sh->args[0]) + 2;
        char full_path[len];

        snprintf(full_path, len, "%s/%s", paths[i], sh->args[0]);
        if (access(full_path, X_OK) == 0)
            return PATH_BIN;
    }
    return NOTFND_BIN;
}

static void run_command(mysh_t *sh, int command_status, char **paths)
{
    char **env = map_node(sh->env, env_to_string);

    if (command_status == LOCAL_BIN)
    {
        execve(sh->args[0], sh->args, env);
        fprintf(stderr, "%s: %s.\n", sh->args[0], strerror(errno));
        free_shell(sh);
        freetab((void **)paths);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; paths && paths[i] != NULL; i++)
    {
        size_t len = strlen(paths[i]) + strlen(sh->args[0]) + 2;
        char full_path[len];

        snprintf(full_path, len, "%s/%s", paths[i], sh->args[0]);
        execve(full_path, sh->args, env);
    }
    fprintf(stderr, "%s: %s.\n", sh->args[0], strerror(errno));
    free_shell(sh);
    freetab((void **)paths);
    freetab((void **)env);
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
        if (WTERMSIG(status) == SIGSEGV || WTERMSIG(status) == SIGFPE)
        {
            fprintf(stderr, WTERMSIG(status) == SIGSEGV ? "Segmentation fault\n" : "Floating exception\n");
            ret = SIGNAL_EXIT(WTERMSIG(status));
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ret;
}

int processes_management(mysh_t *sh)
{
    char **paths = NULL;
    int ret = 0;
    int status = 0;
    pid_t pid;

    if ((pid = fork()) == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        paths = split_by(get_env_var(sh, "PATH"), ":");
        if ((status = get_bin_type(sh, paths)) == 0)
        {
            fprintf(stderr, "%s: Command not found.\n", sh->args[0]);
            freetab((void **)paths);
            free_shell(sh);
            exit(EXIT_FAILURE);
        }
        run_command(sh, status, paths);
    }
    else
        ret = waitprocess(pid);
    return ret;
}

int check_commands(mysh_t *sh)
{
    int exit_status = 0;

    for (int i = 0; BUILTIN_COMMANDS[i] != NULL; i++)
    {
        if (strcmp(BUILTIN_COMMANDS[i], sh->args[0]) == 0)
        {
            exit_status = BUILTIN_FNS[i](sh);
            sh->exit_status = exit_status;
            return exit_status;
        }
    }
    exit_status = processes_management(sh);
    sh->exit_status = exit_status;
    return exit_status;
}
