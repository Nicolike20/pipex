/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:20:37 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/16 12:42:03 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	aux_get_path(t_pipex *vars, int i, char *aux)
{
	aux = ft_strdup(vars->tmp[0]);
	free(vars->tmp[0]);
	vars->tmp[0] = ft_substr(vars->tmp[0], 5, ft_strlen(vars->tmp[0]));
	free(aux);
	i = 0;
	aux = ft_strdup(vars->tmp[i]);
	free(vars->tmp[i]);
	vars->tmp[i] = ft_path_strjoin(aux, vars->cmd[0]);
	free(aux);
	while (access(vars->tmp[i++], X_OK) < 0 && vars->tmp[i])
	{
		free(vars->tmp[i - 1]);
		aux = ft_strdup(vars->tmp[i]);
		free(vars->tmp[i]);
		vars->tmp[i] = ft_path_strjoin(aux, vars->cmd[0]);
		free(aux);
	}
	if (access(vars->tmp[i - 1], X_OK) < 0)
		fail(vars, 1);
	aux = ft_strdup(vars->tmp[i - 1]);
	free(vars->tmp[i - 1]);
	vars->path = ft_strdup(aux);
	free(aux);
}
static void	get_path(t_pipex *vars)
{
	int		i;
	char	*aux;

	i = 0;
	aux = NULL;
	while (vars->env[i] && ft_strncmp(vars->env[i], "PATH=", 5))
		i++;
	if (vars->env[i] == NULL)
		fail(vars, 0);
	vars->tmp = ft_split(vars->env[i], ':');
	aux_get_path(vars, i, aux);
}

static void	parse_path_if(t_pipex *vars, char *argv)
{
	vars->cmd = ft_split(argv, ' ');
	if (argv[0] == '.' || argv[0] == '~' || argv[0] == '/'
		|| access(vars->cmd[0], X_OK) == 0)
	{
		vars->path = ft_strdup(vars->cmd[0]);
		vars->cmd[0] = ft_strrchr(vars->cmd[0], '/');
		vars->cmd[0]++;
		if (access(vars->path, X_OK) < 0)
			fail(vars, 1);
	}
	else
		get_path(vars);
}

static void	parse_path_else(t_pipex *vars, char *argv)
{
	vars->quote_cnt = -1;
	while ((argv[++vars->quote_cnt] != '\'' || argv[vars->quote_cnt] != '"')
		&& argv[vars->quote_cnt])
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
	vars->cmd = malloc(sizeof(char *) * 2 + 1);
	if (vars->cmd == NULL)
		fail(vars, 0);
	vars->cmd[0] = ft_substr(argv, 0, vars->quote_cnt - 1);
	vars->cmd[1] = ft_substr(argv, vars->quote_cnt + 1,
			ft_strlen(argv) - vars->quote_cnt - 2);
	vars->cmd[2] = NULL;
	get_path(vars);
}

void	parse_path(t_pipex *vars, char *argv)
{
	vars->check = argv_check(argv);
	if (vars->check == 0)
		parse_path_if(vars, argv);
	else
		parse_path_else(vars, argv);
}
