/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:44 by aautin            #+#    #+#             */
/*   Updated: 2023/12/13 22:38:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	is_right_agrs(int argc, char *argv[], char *env[])
{
	int	error_id;

	if (is_right_format(int argc, char *argv[]) == 0)
	{
		ft_printf("The number of arguments is invalid.\n");
		return (0);
	}
	error_id = is_right_content(argv, env);
	if (error_id == 1)
	{
		ft_printf("No such file or directory : %s.\n", argv[1]);
		return (0);
	}
	if (error_id == 2)
	{
		
	}
	return (0);
}

int	main(int argc, char *argv[], char *env[])
{
	
	if (is_right_agrs(argc, argv, env, path_tab) == 1)
	return (0);
}
