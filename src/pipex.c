/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:16 by aautin            #+#    #+#             */
/*   Updated: 2024/01/15 17:01:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	execute(char *cmd_path, char **cmd_and_options, t_fds *fds)
{
	close(fds->pipe[1]);
	close(fds->infl_fd);
	execve(cmd_path, cmd_and_options, NULL);
	free(cmd_path);
	free_stab(cmd_and_options);
	close_and_exit(fds->infl_fd, EXIT_FAILURE);
}

void	child_process(t_fds *fds, char *cmd, char **envp, int cmd_nb)
{
	char	*cmd_path;
	char	**cmd_and_options;

	cmd_path = get_cmd_path(cmd, envp);
	if (cmd_path == NULL)
		close_and_exit(fds->infl_fd, EXIT_FAILURE);
	cmd_and_options = ft_split(cmd, ' ');
	if (cmd_and_options == NULL)
	{
		free(cmd_path);
		close_and_exit(fds->infl_fd, EXIT_FAILURE);
	}
	close(fds->pipe[0]);
	if (cmd_nb != 2)
		dup2(fds->pipe[1], STDOUT_FILENO);
	else
	{
		fds->outfl_fd = open(fds->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds->outfl_fd == -1)
		{
			perror(fds->outfile);
			exit(EXIT_FAILURE);
		}
		dup2(fds->outfl_fd, STDOUT_FILENO);
		close(fds->outfl_fd);
	}
	execute(cmd_path, cmd_and_options, fds);
}

void	parent_process(int pipe[2])
{
	close(pipe[1]);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
}

int	main(int argc, char *argv[], char **envp)
{
	t_fds	fds;
	int		pid;
	int		i;

	if (argc > 4)
	{
		fds.outfile = argv[argc - 1];
		fds.infl_fd = open(argv[1], O_RDONLY);
		if (fds.infl_fd == -1)
			return (perror(argv[1]), 1);
		dup2(fds.infl_fd, STDIN_FILENO);
		i = 1;
		while (++i < argc - 1)
		{
			if (pipe(fds.pipe) == -1)
				return (perror("pipe"), 1);
			pid = fork();
			if (pid == -1)
				return (perror("fork"), 1);
			if (pid == 0)
				child_process(&fds, argv[i], envp, argc - i);
			else
				parent_process(fds.pipe);
		}
		close(fds.infl_fd);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
