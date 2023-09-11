/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnegro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:09:32 by mnegro            #+#    #+#             */
/*   Updated: 2023/09/11 16:57:52 by mnegro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/* here_doc: here_doc is a section of code that acts as a separate file;
is a multiline string or a file literal for sending input
streams to other commands and programs.
In a Hereodc, you enclose the text between delimiters,
and the content of the here document is treated as if it were a string.
Usually is used a specific marker or identifier that marks the beginning
and end of the text block (commonly << followed by an identifier). */

/* Gli passo un delimitatore in cui viene slvata una nuova riga \n .
Chiudo l'fd di lettura (fd_pipe[0])
Ciclo la lettura delle righe di input fino a quando non trova il delimitatore; 
nel ciclo, controllo se la riga di input che trova inizia con il delimitatore su cui e' stato salvato lo \n con ft_strncmp:
- se lo trova, chiude lo std_out, libera la memoria ed esce con successo
- se non lo torva, scrive la riga di input nell' fd di scritttura (fd_pipe[1]), poi libera la memoria della riga di input (line) 
  e continua la lettura passando alla riga successiva fintanto che non trova di nuovo un delimitatore
Finito il ciclo, chiude lo std_out, libera la memoria della riga di input e del delimitatore e restituisce 0. */
void	ft_here_doc(t_mini *shell, char *delimiter, int fd)
{
	char	*line;
	char	*del;

	(void)shell;
	signal(SIGINT, ft_sig_here_doc);
	del = ft_strjoin(delimiter, "\n");
	line = "";
	while (line)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!ft_strncmp(line, del, ft_strlen(del) + 1))
		{
			free(line);
			free(del);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	exit(0);
}

/* Vengono creati due fd: uno di lettura (fd_pipe[0]) e uno di scrittura (fd_pipe[1])
	Poi genero un processo figlio col fork().
	Il processo padre (pid > 0) aspetta che il processo figlio finisca tramite waitpid; quando ha finito
	chiude l'fd di scrittura (fd_pipe[1]) e duplica lo std_in (fd_pipe[0]) sul'fd di lettura (fd_pipe[0])
	Chiudo anche l'fd di lettura (fd_pipe[0]) */
    
int	ft_handler_here_doc(t_mini *shell, char *delimiter)
{
	pid_t	pid;
	int		status;
	int		fd_tmp;

	status = 0;
	unlink("/tmp/here_doc");
	fd_tmp = open("/tmp/here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid > 0)
		waitpid(pid, &status, 0);
	else
		ft_here_doc(shell, delimiter, fd_tmp);
	shell->exit_status = WEXITSTATUS(status);
	close(fd_tmp);
	fd_tmp = open("/tmp/here_doc", O_RDONLY);
	return (fd_tmp);
}
