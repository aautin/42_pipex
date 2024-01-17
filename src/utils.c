/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:50:06 by aautin            #+#    #+#             */
/*   Updated: 2024/01/17 22:36:56 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	command_not_found(char *cmd)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(EXIT_FAILURE);
}

void	close_fds(int fds_nb, ...)
{
	int		i;
	va_list	arg;

	va_start(arg, fds_nb);
	i = 0;
	while (i < fds_nb)
	{
		close(va_arg(arg, int));
		i++;
	}
	va_end(arg);
	return ;
}

void	init_conf(t_conf *conf, int argc, char *argv[], char *envp[])
{
	if (conf->here_doc == 1)
	{
		conf->first_cmd = 3;
		conf->last_cmd = 4;
	}
	else
	{
		conf->first_cmd = 2;
		conf->last_cmd = argc - 2;
	}
	conf->argc = argc;
	conf->argv = argv;
	conf->envp = envp;
	conf->fds.outfile = conf->argv[conf->argc - 1];
	conf->fds.infile = conf->argv[1];
}

char	*init_path(t_conf *conf, char *cmd)
{
	char	*str_temp;

	conf->i = 0;
	while (cmd[conf->i] && cmd[conf->i] != ' ')
		conf->i++;
	conf->temp = cmd[conf->i];
	cmd[conf->i] = '\0';
	if (access(cmd, F_OK | X_OK) != -1)
		return (str_temp = ft_strdup(cmd), cmd[conf->i] = conf->temp, str_temp);
	return (NULL);
}

char	*get_cmd_path(t_conf *conf, char *cmd)
{
	char	**paths;

	conf->str = init_path(conf, cmd);
	if (conf->str != NULL)
		return (conf->str);
	conf->j = -1;
	while (conf->envp[++conf->j] && ft_strncmp(conf->envp[conf->j], "PATH=", 5))
		;
	if (conf->envp[conf->j] == NULL)
		command_not_found(cmd);
	paths = ft_split(conf->envp[conf->j] + 5, ':');
	if (paths == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	conf->j = -1;
	while (paths[++conf->j])
	{
		conf->str = ft_strjoin(ft_strjoin(paths[conf->j], "/", 0), cmd, 1);
		if (access(conf->str, F_OK | X_OK) != -1)
			return (cmd[conf->i] = conf->temp, free_stab(paths), conf->str);
		free(conf->str);
	}
	return (free_stab(paths), command_not_found(cmd), NULL);
}
