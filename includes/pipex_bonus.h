/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:07 by aautin            #+#    #+#             */
/*   Updated: 2023/12/29 19:44:40 by aautin           ###   ########.fr       */
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

// pipex_bonus.c
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd, int argc);


#endif