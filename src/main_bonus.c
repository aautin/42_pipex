
#include "../includes/pipex_bonus.h"

static void	execute(char **cmd_w_options, char **env)
{
	char	*cmd_path;

	if (cmd_w_options == NULL)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	cmd_path = get_cmd_path(cmd_w_options[0], env);
	i (cmd_path == NULL)
		return ;
	if (execve(cmd_path, cmd_w_options, NULL) == -1)
	{
		perror(cmd_w_options[0]);
		return ;
	}
	free(cmd_path);
}

static void	process(char *argv, char **env)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(ft_split(argv, ' '), env);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

static void	here_doc(char *limiter, int argc)
{
	// continue here...
}

int	main(int argc, char **argv,  char **env)
{
	int i;
	int	fd_in_out[2];

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fd_in_out[1] = openfile(argv[argc - 1], "outdoc");
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fd_in_out[1] = openfile(argv[argc - 1], "outfile");
			fd_in_out[0] = openfile(argv[0], "infile");			
			dup2(fd_in_out[0], STDIN_FILENO);
		}
		while (i < argc - 2)
			process(argv[i++], env);
		dup2(fd_in_out[1], STDOUT_FILENO);
		execute(ft_split(argv[argc - 2], ' '), env);
	}
	return (ft_printf("Wrong number of arguments.\n") != 0);
}
