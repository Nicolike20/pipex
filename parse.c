/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:20:37 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/11 17:45:54 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_path(t_pipex *vars)
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
