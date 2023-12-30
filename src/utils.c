/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:32 by aautin            #+#    #+#             */
/*   Updated: 2023/12/30 18:24:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **cmd, char **envp)
{
	char	**paths;
	char	*right_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 1);
		paths[i] = ft_strjoin(paths[i], cmd[0], 1);
		if (access(paths[i], F_OK) == 0)
		{
			right_path = ft_strdup(paths[i]);
			free_stab(paths);
			return (right_path);
		}
		i++;
	}
	free_stab(paths);
	return (NULL);
}

void	error(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		error(NULL);
	if (cmd[0][0] == '/')
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd, envp);
	if (!path)
	{
		free_stab(cmd);
		error(NULL);
	}
	if (execve(path, cmd, envp) == -1)
		error(NULL);
	free_stab(cmd);
	free(path);
}
