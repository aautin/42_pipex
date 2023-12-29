/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 12:56:01 by aautin            #+#    #+#             */
/*   Updated: 2023/12/29 20:01:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		infile_fd;

	infile_fd = open(argv[1], O_RDONLY, 0777);
	if (infile_fd == -1)
		error(NULL);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(infile_fd, STDIN_FILENO);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int *fd, int argc)
{
	int		outfile_fd;

	outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error(NULL);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}

int		main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	if (argc >= 5)
	{
		if (pipe(fd) == -1)
			error(NULL);
		pid = fork();
		if (pid == -1)
			error(NULL);
		if (pid == 0)
			child_process(argv, envp, fd);
		else
		{
			waitpid(pid, NULL, 0);
			parent_process(argv, envp, fd, argc);
		}
	}
	else
	{
		ft_printf("Wrong number of arguments");
		ft_printf("./pipex input_file cmd1 cmd2 output_file");
	}
	return (0);
}
