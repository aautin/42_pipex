/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:55:34 by aautin            #+#    #+#             */
/*   Updated: 2024/01/17 17:56:28 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parent_here_doc(t_conf *conf, int pipe[2], pid_t pid)
{
	close(conf->fds.pipe[0]);
	close(pipe[1]);
	dup2(pipe[0], STDIN_FILENO);
	close(pipe[0]);
	waitpid(pid, NULL, 0);
}

static void	here_doc(t_conf *conf, int pipe[2])
{	
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		conf->doc = get_next_line(0);
		while (conf->doc != NULL
			&& (ft_strncmp(conf->doc, conf->argv[2], ft_strlen(conf->argv[2]))
				|| ft_strlen(conf->doc) - 1 != ft_strlen(conf->argv[2])))
		{
			write(pipe[1], conf->doc, ft_strlen(conf->doc));
			free(conf->doc);
			conf->doc = get_next_line(0);
		}
		if (conf->doc)
			free(conf->doc);
		close_fds(4, pipe[0], pipe[1], conf->fds.pipe[0], conf->fds.pipe[1]);
		exit(EXIT_SUCCESS);
	}
	parent_here_doc(conf, pipe, pid);
}

static void	init_input(t_conf *conf, int i)
{
	int		pipe_fd[2];

	if (i == conf->first_cmd && conf->here_doc)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		here_doc(conf, pipe_fd);
	}
	else if (i == conf->first_cmd)
	{
		conf->fds.infl_fd = open(conf->fds.infile, O_RDONLY);
		if (conf->fds.infl_fd == -1)
		{
			perror(conf->fds.infile);
			exit(EXIT_FAILURE);
		}
		dup2(conf->fds.infl_fd, STDIN_FILENO);
		close(conf->fds.infl_fd);
		close(conf->fds.pipe[0]);
	}
	else
		close(conf->fds.pipe[0]);
}	

static void	init_output(t_conf *conf, int i)
{
	if (i == conf->last_cmd)
	{
		conf->fds.outfl_fd = open(conf->fds.outfile, WR | CR | TR, 0644);
		if (conf->fds.outfl_fd == -1)
		{
			perror(conf->fds.outfile);
			exit(EXIT_FAILURE);
		}
		dup2(conf->fds.outfl_fd, STDOUT_FILENO);
		close(conf->fds.outfl_fd);
		close(conf->fds.pipe[1]);
	}
	else
	{
		dup2(conf->fds.pipe[1], STDOUT_FILENO);
		close(conf->fds.pipe[1]);
	}
}

void	child_process(t_conf *conf, int i)
{
	char	*cmd_path;
	char	**cmd_w_options;

	init_input(conf, i);
	init_output(conf, i);
	cmd_path = get_cmd_path(conf, conf->argv[i]);
	cmd_w_options = ft_split(conf->argv[i], ' ');
	if (cmd_w_options == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_w_options, NULL);
	free(cmd_path);
	free_stab(cmd_w_options);
	exit(EXIT_FAILURE);
}
