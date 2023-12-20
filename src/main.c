/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:08:44 by aautin            #+#    #+#             */
/*   Updated: 2023/12/14 17:11:54 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	parent_process(int *fd)
{
	char	*str;

	close(fd[1]);
	str = get_file_content(fd[0]);
	if (!str)
	{
		perror(NULL);
		return ;
	}
	close(fd[0]);
	ft_printf("%s", str);
	free(str);
}

static void	child_process(char **argv, int *fd)
{
	char	*file_content;
	int		file_fd;

	file_fd = open(argv[1], O_RDONLY);
	file_content = get_file_content(file_fd);
	if (!file_content)
	{
		perror(argv[1]);
		return ;
	}
	close(fd[0]);
	write(fd[1], file_content, ft_strlen(file_content));
	free(file_content);
	close(file_fd);
}

int	main(int argc, char **argv,  char **env)
{
	(void) env;
	int		fd[2];
	int		pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
		{
			perror("Error:");
			return (1);
		}
		pid = fork();
		if (pid == 0)
		{
			child_process(argv, fd);
			ft_printf("PID = %d || Parent PID = %d\n", getpid(), getppid());
		}
		else
		{
			waitpid(pid, NULL, 0);
			parent_process(fd);
			ft_printf("PID = %d || Parent PID = %d\n", getpid(), getppid());
		}
		return (0);
	}
	else
	{
		ft_printf("Wrong number of arguments.\n");
		return (1);
	}
}
