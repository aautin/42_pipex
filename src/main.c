/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:44 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 17:11:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	execute(char **cmd_w_options, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd_w_options[0], env);
	if (cmd_path == NULL)
		return ;
	if (execve(cmd_path, cmd_w_options, NULL) == -1)
	{
		perror(cmd_w_options[0]);
		return ;
	}
	free(cmd_path);
}

static void	parent_process(int *fd, char **argv, char **env)
{
	int		outfile_fd;
	char	**cmd_w_options;

	close(fd[1]);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	cmd_w_options = ft_split(argv[3], ' ');
	execute(cmd_w_options, env);
	free_stab(cmd_w_options);
	close(outfile_fd);
}

static void	child_process(char **argv, int *fd, char **env)
{
	int		infile_fd;
	char	**cmd_w_options;

	close(fd[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	dup2(infile_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	cmd_w_options = ft_split(argv[2], ' ');
	execute(cmd_w_options, env);
	free_stab(cmd_w_options);
	close(infile_fd);
}

int	main(int argc, char **argv,  char **env)
{
	int		fd[2];
	int		pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(argv, fd, env);
		else
		{
			waitpid(pid, NULL, 0);
			parent_process(fd, argv, env);
		}
		return (0);
	}
	return (ft_printf("Wrong number of arguments.\n") != 0);
}
