/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:50:46 by aautin            #+#    #+#             */
/*   Updated: 2023/12/13 22:36:25 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	is_right_format(int argc)
{
	if (argc != 5)
		return (0);
	else
		return (1);
}

int	is_right_content(char *argv[], char *env[])
{
	char	**paths
	if (access(argv[1], R_OK) == -1)
		return (1);
	if (access(argv[4], W_OK) == -1)
		return (2);
}