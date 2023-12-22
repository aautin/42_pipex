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

static void	execute(char **cmd_w_options, char **env)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd_w_options[0], env);
	if (cmd_path == NULL)
		return ;
	execve(cmd_path, cmd_w_options, NULL);
	free(cmd_path);
}

static void	parent_process(int *fd, char **argv, char **env)
{
	char	**cmd_w_options;

	close(fd[1]);
	cmd_w_options = ft_split(argv[2], ' ');
	if (cmd_w_options == NULL)
	{
		perror(NULL);
		return ;
	}
	dup2(fd[0], STDIN_FILENO);
	execute(cmd_w_options, env);
	free_stab(cmd_w_options);
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
			parent_process(fd, argv, env);
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
