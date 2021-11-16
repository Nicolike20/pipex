/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:39:08 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/16 12:36:45 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		status;
	char	**env;
	int		pid;
	int		fd_rw[2];
	int		in_fd;
	int		out_fd;
	char	*infile;
	char	*outfile;
	char	**cmd;
	char	*path;
	char	*line;
	int		check;
	char	**tmp;
	int		tmp_i;
	int		quote_cnt;
	int		quote_check;
	int		quote_tmp;
}t_pipex;

void	fail(t_pipex *vars, int code);
void	father_son(t_pipex *vars, char *argv);
int		argv_check(char *argv);
void	parse_path(t_pipex *vars, char *argv);
void	here_doc_pipex(t_pipex *vars, int argc, char **argv, int i);

#endif
