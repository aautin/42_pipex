/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:49:59 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 19:53:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_env_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(env[i], ':');
	if (paths == NULL)
	{
		perror(NULL);
		return (NULL);
	}
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/", 1);
		if (paths[i] == NULL)
		{
			frees(2, 'S', paths, 'S', paths + (++i)); // free dbtab from first
			perror(NULL);
			return (NULL);	// to the crash one, & from the next to the last
		}
	}
	return (paths);
}

char	*get_cmd_path(char *cmd_no_option, char **env)
{
	char	**env_paths;
	char	*temp;
	int		i;

	env_paths = get_env_paths(env);
	if (env_paths == NULL)
		return (NULL);
	i = 0;
	while (env_paths[i])
	{
		temp = ft_strjoin(env_paths[i], cmd_no_option, 0);
		if (access(temp, X_OK) != -1)
		{
			free_stab(env_paths);
			return (temp);
		}
		free(temp);
		i++;
	}
	ft_printf("command not found: %s\n", cmd_no_option);
	free_stab(env_paths);
	return (NULL);
}