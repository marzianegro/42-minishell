#include "../minishell.h"

/*
HEREDOCK
Hereodc is a section of code that acts as a separate file;
is a multiline string or a file literal for sending input
streams to other commands and programs.
In a Hereodc, you enclose the text between delimiters,
and the content of the here document is treated as if it were a string.
Usually is used a specific marker or identifier that marks the beginning
and end of the text block (commonly << followed by an identifier).
UNLINK()
is used to remove a file from the filesystem,It deletes the directory entry for a file
*/

int ft_here_doc(t_mini *shell, char *del)
{
    int pid;
    signal(SIGINT, ft_handle_signal_heredoc);


}