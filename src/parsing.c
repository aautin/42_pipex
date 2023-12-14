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

static int	get_paths_line(char *env[])
{
	int	i;
	int found;
	int	line_len;

	i = 0;
	found = 0;
	while (env[i])
	{
		line_len = ft_strlen(env[i]);
		if (ft_strnstr(env[i], "PATH", line_len))
		{
			if (found)
				return (i);
			else
				found = 1;
		}
		i++;
	}
	return (-1);
}

char	**get_paths_tab(char *env[])
{
	char	**tab;
	int		paths_line;
	int		i;

	paths_line = get_paths_line(env);
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
