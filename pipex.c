/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:38:32 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/16 13:17:36 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	argv_check(char *argv)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i] == '\'' || argv[i] == '\"')
			return (1);
	}
	return (0);
}

void	fail(t_pipex *vars, int code)
{
	vars = NULL;
	if (code == 0)
		write(2, "Error\n", 6);
	if (code == 1)
		write(2, "Command not found\n", 18);
	if (code == 2)
		write(2, "Pipe or fork error\n", 19);
	if (code == 3)
		write(2, "Expected valid infile\n", 22);
	exit(2);
}

void	father_son(t_pipex *vars, char *argv)
{
	int	status;

	if (pipe(vars->fd_rw) == -1)
		fail(vars, 2);
	vars->pid = fork();
	if (vars->pid < 0)
		fail(vars, 2);
	if (vars->pid > 0)
	{
		close(vars->fd_rw[1]);
		dup2(vars->fd_rw[0], STDIN_FILENO);
		close(vars->fd_rw[0]);
		waitpid(vars->pid, &status, 0);
		if (WEXITSTATUS(status) == 2)
			exit(2);
	}
	else
	{
		close(vars->fd_rw[0]);
		dup2(vars->fd_rw[1], STDOUT_FILENO);
		close(vars->fd_rw[1]);
		parse_path(vars, argv);
		execve(vars->path, vars->cmd, vars->env);
	}
}

static void	normal_pipex(t_pipex *vars, int argc, char **argv, int i)
{
	vars->in_fd = open(vars->infile, O_RDONLY);
	if (vars->in_fd <= 0)
		fail(vars, 3);
	dup2(vars->in_fd, STDIN_FILENO);
	close(vars->in_fd);
	vars->out_fd = open(vars->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (vars->out_fd <= 0)
		fail(vars, 0);
	while (++i < argc - 2)
		father_son(vars, argv[i]);
	parse_path(vars, argv[i]);
	dup2(vars->out_fd, STDOUT_FILENO);
	close(vars->out_fd);
	execve(vars->path, vars->cmd, vars->env);
}

void	leak(void)
{
	system("leaks -q pipex > leaks");
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	t_pipex		vars;
	int			i;

	atexit(leak);
	i = 1;
	if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		vars.env = environ;
		vars.infile = ft_strdup(argv[1]);
		vars.outfile = ft_strdup(argv[argc - 1]);
		normal_pipex(&vars, argc, argv, i);
	}
	else if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		vars.env = environ;
		vars.out_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (vars.out_fd <= 0)
			fail(&vars, 0);
		here_doc_pipex(&vars, argc, argv, i);
	}
	else
		write (2, "Invalid arguments\n", 18);
	return (0);
}
