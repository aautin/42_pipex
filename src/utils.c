/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:11:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/15 15:59:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(char *cmd)
{
	write(2, "command not found: ", 19);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	close_and_exit(int infile, int exit_code)
{
	close(infile);
	exit(exit_code);
}

char	*get_cmd_no_option(char *cmd)
{
	int		i;
	int		j;
	char	*cmd_no_option;

	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	cmd_no_option = malloc(sizeof(char) * (i + 1));
	if (cmd_no_option == NULL)
		return (NULL);
	while (j < i)
	{
		cmd_no_option[j] = cmd[j];
		j++;
	}
	cmd_no_option[j] = '\0';
	return (cmd_no_option);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_no_option;
	char	*cmd_path;
	int		i;

	i = -1;
	while (ft_strncmp(envp[++i], "PATH=", 5) != 0)
		if (envp[i] == NULL)
			return (perror("PATH not found"), NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	cmd_no_option = get_cmd_no_option(cmd);
	if (cmd_no_option == NULL)
		return (free_stab(paths), NULL);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], "/", 0);
		cmd_path = ft_strjoin(cmd_path, cmd_no_option, 1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_stab(paths), free(cmd_no_option), cmd_path);
		free(cmd_path);
	}
	return (error(cmd_no_option), free_stab(paths), free(cmd_no_option), NULL);
}
