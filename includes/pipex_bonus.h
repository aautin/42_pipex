/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:07 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 17:37:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

// utils_bonus.c
char		**get_env_paths(char **env);
char		*get_cmd_path(char *cmd_no_option, char **env);
int			openfile(char *filename, char *option);

// main.c
int			main(int argc, char **argv,  char **env);

#endif