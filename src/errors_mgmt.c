/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:50:46 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 19:55:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	does_cmd_exist(char **paths_tab, char *cmdname)
{
	int		i;
	char	*cmdpath_nooption;
	char	**cmdname_tab;

	cmdname_tab = ft_split(cmdname, ' ');
	if (cmdname_tab == NULL)
		return (0);
	i = 0;
	while (paths_tab[i])
	{
		cmdpath_nooption = ft_strjoin(paths_tab[i], cmdname_tab[0], 0);
		if (execve(cmdpath_nooption, cmdname_tab, NULL) != -1)
		{
			free(cmdpath_nooption);
			free(cmdname_tab);
			return (1);
		}
		free(cmdpath_nooption);
		i++;
	}
	perror(cmdname_tab[0]);
	free(cmdname_tab);
	return (0);
}

int		files_check(char *filename1, char *filename2)
{
	if (access(filename2, W_OK) == -1 && access(filename1, R_OK) == -1)
	{
		perror(filename1);
		return (3);
	}
	if (access(filename1, R_OK) == -1)
	{
		perror(filename1);
		return (1);
	}
	if (access(filename2, W_OK) == -1)
		return (2);
	return (0);
}

char	**args_check(int argc, char *argv[], char *env[])
{
	char	**paths_tab;
	int		check;
	if (argc != 5)
	{
		ft_printf("The number of arguments is invalid.\n");
		return (NULL);
	}
	check = files_check(argv[1], argv[4]);
	if (check == 1 || check == 3)
		return (NULL);
	paths_tab = get_paths_tab(env);
	if (paths_tab == NULL)
		return (NULL);
	if (!does_cmd_exist(paths_tab, argv[2])
		|| !does_cmd_exist(paths_tab, argv[3]))
	{
		free_tab(paths_tab);
		return (NULL);
	}
	return (paths_tab);
}
