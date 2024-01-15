/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/15 17:01:35 by aautin           ###   ########.fr       */
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

typedef struct s_fds
{
	int		pipe[2];
	int		infl_fd;
	int		outfl_fd;
	char	*infile;
	char	*outfile;
}				t_fds;

// utils.c
void	error(char *cmd);
void	close_and_exit(int infile, int exit_code);
char	*get_cmd_no_option(char *cmd);
char	*get_cmd_path(char *cmd, char **envp);

// pipex.c
void	execute(char *cmd_path, char **cmd_and_options, t_fds *fds);
void	child_process(t_fds *fds, char *cmd, char **envp, int cmd_nb);
void	parent_process(int pipe[2]);
int		main(int argc, char *argv[], char **envp);

#endif