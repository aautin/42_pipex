/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:50:06 by aautin            #+#    #+#             */
/*   Updated: 2024/01/16 21:07:52 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_conf(t_conf *conf, int argc, char *argv[], char *envp[])
{
	conf->argc = argc;
	conf->argv = argv;
	conf->envp = envp;
	conf->fds.outfile = conf->argv[conf->argc - 1];
	conf->fds.infile = conf->argv[1];
}

char	*get_cmd_path(t_conf *conf, char *cmd)
{
	char	temp;
	char	**paths;
	char	*str_temp;
	int		i;
	int		j;

	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	temp = cmd[i];
	cmd[i] = '\0';
	if (access(cmd, F_OK | X_OK) != -1)
	{
		str_temp = ft_strdup(cmd);
		cmd[i] = temp;
		return (str_temp);
	}
	j = -1;
	while (ft_strnstr(conf->envp[++j], "PATH=", 5) == NULL)
	{
		if (conf->envp[j] == NULL)
		{
			ft_putstr_fd("command not found: ", 2);
			ft_putendl_fd(cmd, 2);
			exit(EXIT_FAILURE);
		}
	}
	paths = ft_split(conf->envp[j] + 5, ':');
	if (paths == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	j = -1;
	while (paths[++j])
	{
		str_temp = ft_strjoin(paths[j], "/", 0);
		str_temp = ft_strjoin(str_temp, cmd, 1);
		if (access(str_temp, F_OK | X_OK) != -1)
		{
			cmd[i] = temp;
			return (free_stab(paths), str_temp);
		}
		free(str_temp);
	}
	free_stab(paths);
	ft_putstr_fd("command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	exit(EXIT_FAILURE);
}
