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
	char	*file_content;

	file_content = get_file_content(argv[1]);
	if (!file_content)
	{
		perror(file_content);
		return ;
	}
	ft_printf("%s", file_content);
	free(file_content);
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
