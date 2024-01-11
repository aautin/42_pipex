/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:07 by aautin            #+#    #+#             */
/*   Updated: 2023/12/30 18:17:13 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

// utils.c
char	*find_path(char *cmd, char **envp);
void	error(char *msg);
void	execute(char *argv, char **envp);

// utils_bonus.c
void	print_and_exit(char *msg);
void	read_until_limiter(char *limiter, int fd_out);
void	here_doc(char *limiter, int argc);

// pipex_bonus.c
int		openfile(char *filename, char *filetype);
void	child_process(char *argv, char **envp);
void	parent_process(int outfile_fd);

#endif