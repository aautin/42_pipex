/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
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
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

// utils.c
void		free_tab(char **tab);

// errors_mgmt.c
int			files_check(char *filename1, char *filename2);
char		**args_check(int ac, char *av[], char *env[]);

// parsing.c
char		*get_cmdname_nooption(char *cmdname);
char		**get_paths_tab(char *env[]);

// main.c
int			main(int argc, char *argv[], char *env[]);

#endif