/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/16 21:09:29 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define WR O_WRONLY
# define CR O_CREAT
# define TR O_TRUNC

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
}	t_fds;

typedef struct s_conf
{
	t_fds	fds;
	int		argc;
	char	**argv;
	char	**envp;
}	t_conf;

// utils.c
void	init_conf(t_conf *conf, int argc, char *argv[], char *envp[]);
char	*get_cmd_path(t_conf *conf, char *cmd);

// child_process.c
void	child_process(t_conf *conf, int i);

// pipex.c
void	pipex(t_conf *conf);

#endif