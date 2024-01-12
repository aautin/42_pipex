/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:16 by aautin            #+#    #+#             */
/*   Updated: 2024/01/12 20:02:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int pipe[2], char *cmd, char **envp)
{
	close(pipe[0]);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	execve(cmd, envp, NULL);
}

int	main(int argc, char *argv[], char **envp)
{
	int		infile;
	int		pid;
	(void)	envp;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			return (perror(argv[1]), 1);
		argc = 2;
		while (argc < 6)
		{
			pid = fork();
			if (pid == -1)
				return (perror("fork"), 1);
			if (pid == 0)
			{
				ft_printf("child = PID: %5d | PPID: %5d\n", getpid(), getppid());
				exit(EXIT_SUCCESS);
			}
			else
			{
				ft_printf("parent= PID: %5d | PPID: %5d\n", getpid(), getppid());
			}
			argc++;
		}
		while (waitpid(-1, NULL, 0) != -1)
			ft_printf("suisse\n");
		ft_printf("suisse\n");
	}
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
