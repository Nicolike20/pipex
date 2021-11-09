/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:38:32 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/09 20:10:05 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>

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
	/*if (code == 3)
		write(2, "Close the quotation marks\n", 26);*/
	exit(2);
}

void	get_path(t_pipex *vars)
{
	int		i;
	char	**tmp;

	i = 0;
	while (ft_strncmp(vars->env[i], "PATH=", 5))
		i++;
	tmp = ft_split(vars->env[i], ':');
	tmp[0] = ft_substr(tmp[0], 5, ft_strlen(tmp[0]));
	i = 0;
	tmp[i] = ft_strjoin(tmp[i], "/");
	tmp[i] = ft_strjoin(tmp[i], vars->cmd[0]);
	while (access(tmp[i++], X_OK) < 0 && tmp[i])
	{
		tmp[i] = ft_strjoin(tmp[i], "/");
		tmp[i] = ft_strjoin(tmp[i], vars->cmd[0]);
	}
	if (access(tmp[i - 1], X_OK) < 0)
		fail(vars, 1);
	vars->path = ft_strdup(tmp[i - 1]);
}

/*int	check_again(t_pipex *vars, char *argv)
{
	vars->quote_tmp = vars->quote_cnt;
	while (argv[++vars->quote_tmp])
	{
		if (argv[vars->quote_tmp] == '\'' && vars->quote_check == 0)
			return (0);
		if (argv[vars->quote_tmp] == '\"' && vars->quote_check == 1)
			return (0);
	}
	return (1);
}*/

void	parse_path(t_pipex *vars, char *argv)
{
	vars->check = argv_check(argv);
	if (vars->check == 0)
	{
		vars->cmd = ft_split(argv, ' ');
		if (argv[0] == '.' || argv[0] == '~' || argv[0] == '/'
			|| access(vars->cmd[0], X_OK) == 0)
		{
			vars->path = ft_strdup(vars->cmd[0]);
			vars->cmd[0] = ft_strrchr(vars->cmd[0], '/');
			vars->cmd[0]++;
		}
		else
		{
			get_path(vars);
		}
	}
	else
	{
		vars->quote_cnt = -1;
		while ((argv[++vars->quote_cnt] != '\'' || argv[vars->quote_cnt] != '"') && argv[vars->quote_cnt])
		{
			if (argv[vars->quote_cnt] == '\'')
			{
				vars->quote_check = 0;
				break ;
			}
			if (argv[vars->quote_cnt] == '"')
			{
				vars->quote_check = 1;
				break ;
			}
		}
		/*if (check_again(vars, argv))
			fail(vars, 3);*/
		vars->cmd = malloc(sizeof(char *) * 2 + 1);
		if (vars->cmd == NULL)
			fail(vars, 0);//mega_free?
		vars->cmd[0] = ft_substr(argv, 0, vars->quote_cnt - 1);
		vars->cmd[1] = ft_substr(argv, vars->quote_cnt + 1, ft_strlen(argv) - vars->quote_cnt - 2);
		vars->cmd[2] = NULL;
		get_path(vars);
	} //mega_free?
}

void	father_son(t_pipex *vars, char *argv)
{
	//TODO: cerrar ends de las pipes;
	if (pipe(vars->fd_rw) == -1)
		fail(vars, 2);
	vars->pid = fork(); //0 hijo, > 0 padre, -1 error;
	if (vars->pid < 0)
		fail(vars, 2);
	if (vars->pid > 0) //padre
	{
		close(vars->fd_rw[1]);
		dup2(vars->fd_rw[0], STDIN_FILENO);
		close(vars->fd_rw[0]);
		waitpid(vars->pid, NULL, 0);
	}
	else
	{
		close(vars->fd_rw[0]);
		dup2(vars->fd_rw[1], STDOUT_FILENO);
		close(vars->fd_rw[1]);
		parse_path(vars, argv);
		//execve(path, char ** con cosas, env);
		execve(vars->path, vars->cmd, vars->env);
		//system("leaks -q a.out > leaks");
	}
}

void	here_doc(t_pipex *vars, char *delim)
{
	char	*del;

	del = ft_strjoin(delim, "\n");
	if (pipe(vars->fd_rw) < 0)
		fail(vars, 2);
	vars->pid = fork();
	if (vars->pid < 0)
		fail(vars, 2);
	if (vars->pid > 0)
	{
		close(vars->fd_rw[1]);
		dup2(vars->fd_rw[0], STDIN_FILENO);
		close(vars->fd_rw[0]);
		waitpid(vars->pid, NULL, 0);
	}
	else
	{
		close(vars->fd_rw[0]);
		vars->line = get_next_line(STDIN_FILENO);
		while (vars->line)
		{
			if (ft_strncmp(vars->line, del, ft_strlen(del) + 1) == 0)
			{
				close(vars->fd_rw[1]);
				free(vars->line);
				exit(0);
			}
			ft_putstr_fd(vars->line, vars->fd_rw[1]);
			free(vars->line);
			vars->line = get_next_line(STDIN_FILENO);
		}
	}
}

/*void	leak(void)
{
	system("leaks -q a.out > leaks");
	system("lsof -c a.out > fdleaks");
}*/

//READ_END -> 0, WRITE_END -> 1;
//en hijo, cerrar fd[0] (lectura), en padre cerrar fd[1] (escritura);
int	main(int argc, char **argv)
{
	extern char	**environ;
	t_pipex		vars;
	int			i;

	//atexit(leak);
	i = 1;
	if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 9) != 0)
	{
		//init de vars;
		vars.env = environ;
		vars.infile = ft_strdup(argv[1]); //cambiar a argv si no lo muevo a otra funcion lol;
		vars.outfile = ft_strdup(argv[argc - 1]);
		vars.in_fd = open(vars.infile, O_RDONLY);
		if (vars.in_fd <= 0)
			return (0);
		dup2(vars.in_fd, STDIN_FILENO);
		close(vars.in_fd);
		vars.out_fd = open(vars.outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (vars.out_fd <= 0)
			fail(&vars, 0);
		while (++i < argc - 2)
			father_son(&vars, argv[i]);
		parse_path(&vars, argv[i]);
		dup2(vars.out_fd, STDOUT_FILENO);
		close(vars.out_fd);
		execve(vars.path, vars.cmd, vars.env);
	}
	else if (argc >= 5 && ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		vars.env = environ;
		//vars.outfile = ft_strdup(argv[argc - 1]);
		vars.out_fd = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (vars.out_fd <= 0)
			fail(&vars, 0);
		here_doc(&vars, argv[2]);
		i++;
		while (++i < argc - 2)
			father_son(&vars, argv[i]);
		parse_path(&vars, argv[i]);
		dup2(vars.out_fd, STDOUT_FILENO);
		close(vars.out_fd);
		execve(vars.path, vars.cmd, vars.env);
	}
	else
		write (2, "Invalid arguments\n", 18);
	return (0);
}
