/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:49:59 by aautin            #+#    #+#             */
/*   Updated: 2023/12/13 22:14:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	get_pathsline(char *env[])
{
	int	i;
	int	line_len;

	i = 0;
	while (env[i])
	{
		line_len = ft_strlen(env[i]);
		if (ft_strnstr(env[i], "PATH", line_len))
			return (i);
		i++;
	}
	return (-1);
}

char	*commands_paths(char *env[])
{
	char	**tab;
	int		paths_line;
	int		i;

	paths_line = get_pathsline(env);
	if (paths_line == -1)
		return (NULL);
	tab = ft_split(env[paths_line], ':');
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strjoin(tab[i], "/", 1);
		i++;
	}
	return (tab);
}
