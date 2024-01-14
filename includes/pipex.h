/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/14 20:53:16 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// define with ifndef and endif the .h

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft_extended.h"
# include <errno.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

// utils.c
void	error(char *cmd);
void	close_and_exit(int infile, int exit_code);
char	*get_cmd_no_option(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

// pipex.c
void	child_process(int pipe[2], char *cmd, char **envp, int infile);
void	parent_process(int pipe[2]);
void	final_process(int pipe[2], char *outfile);
int		main(int argc, char *argv[], char **envp);

#endif