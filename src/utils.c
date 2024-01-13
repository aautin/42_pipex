/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:11:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/13 21:17:08 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_and_exit(int infile, int exit_code)
{
	close(infile);
	exit(exit_code);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**path_dirs;
	char	*cmd_path;
	int		i;

	i = -1;
	while (ft_strncmp(envp[++i], "PATH=", 5) != 0)
		if (envp[i] == NULL)
			return (NULL);
	path_dirs = ft_split(envp[i] + 5, ':');
	if (path_dirs == NULL)
		return (NULL);
	i = -1;
	while (path_dirs[++i])
	{
		cmd_path = ft_strjoin(path_dirs[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, cmd, 1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_stab(path_dirs), cmd_path);
		free(cmd_path);
	}
	return (free_stab(path_dirs), NULL);
}
