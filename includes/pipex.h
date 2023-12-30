/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:07 by aautin            #+#    #+#             */
/*   Updated: 2023/12/30 18:15:03 by aautin           ###   ########.fr       */
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

// utils.c
char	*find_path(char **cmd, char **envp);
void	error(char *err_msg);
void	execute(char *argv, char **envp);

// pipex.c
int		openfile(char *filename, char *filetype);
void	child_process(char *argv, char **envp);
void	parent_process(int outfile_fd);


#endif