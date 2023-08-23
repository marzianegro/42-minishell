#include "../minishell.h"
/*
dup2(): duplicates an open file descriptor to another file descriptor;
used for redirecting input and output streams,changing the target of a
file descriptor, or setting up communication between processes:
int dup2(int oldfd, int newfd)*/

void ft_dup(t_mini *shell, int oldfd, int newfd)
{
    if (oldfd != -1)
        dup2(oldfd, 0);
    else if (shell->fd_input != -2)
        dup2(shell->fd_input, 0);
    if (newfd != -1)
        dup2(newfd, 1);
    else if (shell->fd_output != -2)
        dup2(shell->fd_output, 1);
}