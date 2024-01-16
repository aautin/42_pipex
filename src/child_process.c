/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:55:34 by aautin            #+#    #+#             */
/*   Updated: 2024/01/16 21:09:45 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_input(t_conf *conf, int i)
{
	if (i == 2)
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
	{
		close(conf->fds.pipe[0]);
	}
}	

void	init_output(t_conf *conf, int i)
{
	if (i == conf->argc - 2)
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
