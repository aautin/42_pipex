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

static void	child_process(char **argv)
{
	char	*str;
	char	*temp;
	int		file_fd;

	file_fd = open(argv[1], O_RDONLY);
	temp = get_next_line(file_fd);
	str = NULL;
	while (temp)
	{
		if (str)
			str = ft_strjoin(str, temp, 2);
		else
		{
			str = ft_strdup(temp);
			free(temp);
		}
		temp = get_next_line(file_fd);
	}
	ft_printf("in.fl's content:\n%s", str);
	frees(1, 's', str);
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
			child_process(argv);
			ft_printf("PID = %d || Parent PID = %d\n", getpid(), getppid());
		}
		else
		{
			waitpid(pid, NULL, 0);
			// parent_process(fd);
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
