/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 12:56:01 by aautin            #+#    #+#             */
/*   Updated: 2023/12/30 18:15:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	openfile(char *filename, char *filetype)
{
	int	fd;

	if (ft_strncmp(filetype, "infile", 6) == 0)
		fd = open(filename, O_RDONLY);
	if (ft_strncmp(filetype, "outfile", 7) == 0)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error(filename);
	return (fd);
}

void	child_process(char *argv, char **envp)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		error(NULL);
	pid = fork();
	if (pid == -1)
		error(NULL);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	parent_process(int outfile_fd)
{
	char	*content;

	content = get_file_content(STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	if (content)
	{
		write(STDOUT_FILENO, content, ft_strlen(content));
		free(content);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	outfile_fd;

	if (argc == 5)
	{
		outfile_fd = openfile(argv[argc - 1], "outfile");
		dup2(openfile(argv[1], "infile"), STDIN_FILENO);
		child_process(argv[2], envp);
		child_process(argv[3], envp);
		parent_process(outfile_fd);
	}
	else
		ft_printf("Wrong number of arguments\n");
	return (0);
}
