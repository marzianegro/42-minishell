#include "../minishell.h"


/* execve: esegue un programma con riferimento a un pathname (il programma
	runnnato dal processo viene rimpiazzato da un nuovo programma i cui elemneti
	vengono inizializzati)

	WEXITSTATUS: macro che ritorna l'exitcode specificato dal processo figlio, 
	ovvero lo stato di uscita del figlio;
	#include <sys/wait.h>
	int WEXITSTATUS(int status) : status = wait o waitpid function */
void	ft_exec_binary(t_mini *shell, t_token *tkn)
{
	pid_t	pid;
	int		status;

	ft_get_token(shell, tkn);
	pid = fork();
	if (!pid)
	{
		execve(tkn->toby[0], tkn->toby, shell->envp);
		if (waitpid(pid, &status, 0) == -1) // equivale a (WEXITSTATUS(EXIT_FAILURE) != 1)
		{
			ft_putstr_fd(&tkn->toby[0][ft_path(tkn->toby[0])], 2); //fare ft_path
			ft_putstr_fd(": command not found\n", 2);
			//free(shell); //forse serve funzione di free shell
			//exit(1);
		}
		perror(&tkn->toby[0][ft_endpath(tkn->toby[0])]);
		//free(shell); //forse serve funzione di free shell
		//exit(1); //valutare se exit(EXIT_FAILURE)
	}
	waitpid(pid, &status, 0);
	shell->exit_status = WEXITSTATUS(status);
}