/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:13:32 by aautin            #+#    #+#             */
/*   Updated: 2023/12/30 18:17:25 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	print_and_exit(char *msg)
{
	ft_printf(msg);
	exit(EXIT_FAILURE);
}

void	read_until_limiter(char *limiter, int fd_out)
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strnstr(line, limiter, ft_strlen(limiter)) != NULL
			&& ft_strlen(limiter) == ft_strlen(line) - 1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd_out, line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	here_doc(char *limiter, int argc)
{
	int	pid;
	int	fd[2];

	if (argc != 6)
		print_and_exit("Wrong number of arguments (here_doc case)");
	if (pipe(fd) == -1)
		error(NULL);
	pid = fork();
	if (pid == -1)
		error(NULL);
	if (pid == 0)
	{
		close(fd[0]);
		read_until_limiter(limiter, fd[1]);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}
