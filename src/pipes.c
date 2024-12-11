#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "environment.h"
#include "utils.h"

static const char *DELIMITERS = " \n\t";

static int count_pipes(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '|')
            count++;
    }
    return count;
}

static int pipe_checks(int pipesnb, int *pipefds, char **pipe_cmds)
{
    if (pipesnb == 0)
        return NOPIPES;
    if ((pipesnb + 1) != tablen((void **)pipe_cmds))
    {
        fprintf(stderr, "Invalid null command.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < pipesnb; i++)
    {
        if (pipe(pipefds + i * 2) == -1)
        {
            perror("pipe");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

static int process_pipe_cmds(mysh_t *sh, char **pipe_cmds, int *pipefds, int pipesnb)
{
    char **args = NULL;
    int res = 0;
    pid_t pid;

    for (int i = 0; pipe_cmds[i] != NULL; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            return EXIT_FAILURE;
        }

        if (pid == 0)
        {
            // Redirect input if not the first command
            if (i != 0)
                dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            // Redirect output if not the last command
            if (pipe_cmds[i + 1] != NULL)
                dup2(pipefds[i * 2 + 1], STDOUT_FILENO);

            for (int j = 0; j < (2 * pipesnb); j++)
                close(pipefds[j]);

            args = split_by(pipe_cmds[i], DELIMITERS);
            if (args[0] == NULL)
            {
                freetab((void **)args);
                continue;
            }
            sh->args = eval_variables(sh, args);
            res = check_commands(sh);
            freetab((void **)args);
            freetab((void **)pipe_cmds);
            // free_shell(sh);
            exit(EXIT_FAILURE);
        }
    }
    return res;
}

int check_pipes(mysh_t *sh, char *line)
{
    int pipe_res = 0;
    int pipes_nb = count_pipes(line);
    char **pipe_cmds = split_by(line, "|\n");
    int pipefds[2 * pipes_nb];

    if ((pipe_res = pipe_checks(pipes_nb, pipefds, pipe_cmds)) != EXIT_SUCCESS)
    {
        freetab((void **)pipe_cmds);
        return pipe_res;
    }
    process_pipe_cmds(sh, pipe_cmds, pipefds, pipes_nb);
    for (int i = 0; i < 2 * pipes_nb; i++)
        close(pipefds[i]);
    for (int i = 0; i <= pipes_nb; i++)
        wait(NULL);
    freetab((void **)pipe_cmds);
    return 0;
}
