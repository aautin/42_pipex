/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:44 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 17:11:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	char	**paths_tab;
	// char	*cmds_paths[2];

	paths_tab = args_check(argc, argv, env);
	if (paths_tab == NULL)
		return (1);
	else
	{
		// pipex();
		return (0);
	}
}
