/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:12:35 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/11 16:18:17 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	here_doc_father(t_pipex *vars)
{
	close(vars->fd_rw[1]);
	dup2(vars->fd_rw[0], STDIN_FILENO);
	close(vars->fd_rw[0]);
	waitpid(vars->pid, NULL, 0);
}

static void	here_doc_son(t_pipex *vars, char *del)
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

static void	here_doc(t_pipex *vars, char *delim)
{
	char	*del;

	del = ft_strjoin(delim, "\n");
	if (pipe(vars->fd_rw) < 0)
		fail(vars, 2);
	vars->pid = fork();
	if (vars->pid < 0)
		fail(vars, 2);
	if (vars->pid > 0)
		here_doc_father(vars);
	else
		here_doc_son(vars, del);
}

void	here_doc_pipex(t_pipex *vars, int argc, char **argv, int i)
{
	here_doc(vars, argv[2]);
	i++;
	while (++i < argc - 2)
		father_son(vars, argv[i]);
	parse_path(vars, argv[i]);
	dup2(vars->out_fd, STDOUT_FILENO);
	close(vars->out_fd);
	execve(vars->path, vars->cmd, vars->env);
}
