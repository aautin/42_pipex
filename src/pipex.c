/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:16 by aautin            #+#    #+#             */
/*   Updated: 2024/01/14 21:03:16 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int pipe[2], char *cmd, char **envp, int infile)
{
	char	*cmd_path;
	char	**cmd_and_options;

	cmd_path = get_cmd_path(cmd, envp);
	if (cmd_path == NULL)
		close_and_exit(infile, EXIT_FAILURE);
	cmd_and_options = ft_split(cmd, ' ');
	if (cmd_and_options == NULL)
	{
		free(cmd_path);
		close_and_exit(infile, EXIT_FAILURE);
	}
	close(pipe[0]);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	close(infile);
	if (execve(cmd_path, cmd_and_options, NULL) == -1)
	{
		free(cmd_path);
		free_stab(cmd_and_options);
		close_and_exit(infile, EXIT_FAILURE);
	}
}

void	parent_process(int pipe[2])
{
	close(pipe[1]);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
}

void	final_process(int pipe[2], char *outfile)
{
	int		outfile_fd;
	char	buf;

	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror(outfile);
		exit(EXIT_FAILURE);
	}
	close(pipe[1]);
	while (read(STDIN_FILENO, &buf, 1) > 0)
		write(outfile_fd, &buf, 1);
	close(outfile_fd);
	close(pipe[0]);
}

int	main(int argc, char *argv[], char **envp)
{
	int		infile;
	int		pipe_fd[2];
	int		pid;

	if (argc == 5)
	{
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			return (perror(argv[1]), 1);
		dup2(infile, STDIN_FILENO);
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(pipe_fd, argv[2], envp, infile);
		else
			parent_process(pipe_fd);
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			child_process(pipe_fd, argv[3], envp, infile);
		else
			parent_process(pipe_fd);
		close(infile);
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		final_process(pipe_fd, argv[4]);
	}
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
