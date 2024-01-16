/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:50:03 by aautin            #+#    #+#             */
/*   Updated: 2024/01/16 21:12:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_conf *conf)
{
	int	i;

	i = 2;
	while (i < conf->argc - 1)
	{
		if (pipe(conf->fds.pipe) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (fork() == 0)
			child_process(conf, i);
		else
		{
			close(conf->fds.pipe[1]);
			dup2(conf->fds.pipe[0], STDIN_FILENO);
			close(conf->fds.pipe[0]);
		}
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_conf	conf;

	if (argc < 4)
		ft_printf("Wrong number of arguments\n");
	else
	{
		init_conf(&conf, argc, argv, envp);
		pipex(&conf);
		while (waitpid(-1, NULL, 0) > 0)
			;
	}
	return (0);
}
