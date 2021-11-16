/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:04:37 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/15 18:41:28 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	res = (char *) malloc(sizeof(char) * (i + 1));
	if (!(res))
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		res[j] = s1[j];
		j++;
	}
	res[j] = s1[j];
	return (res);
}*/

char	*result_line(char **st)
{
	char	*res;
	char	*tmp;
	int		cc;

	cc = 0;
	res = NULL;
	while ((*st)[cc] != '\n' && (*st)[cc])
		cc++;
	if ((*st)[cc] == '\n')
	{
		res = ft_substr(*st, 0, cc + 1);
		tmp = ft_strdup(*st + cc + 1);
		free(*st);
		*st = tmp;
		if (**st == '\0')
		{
			free(*st);
			*st = NULL;
		}
		return (res);
	}
	res = ft_strdup(*st);
	free(*st);
	*st = NULL;
	return (res);
}

char	*buf_checker(char **st, int n)
{
	if (n < 0)
		return (NULL);
	if (!n && (!st || !*st))
		return (NULL);
	return (result_line(st));
}

char	*get_next_line(int fd)
{
	static char	*st;
	char		*buf;
	int			n;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	while (n > 0)
	{
		buf[n] = '\0';
		if (st == NULL)
			st = ft_strdup("");
		tmp = ft_strjoin(st, buf);
		free(st);
		st = tmp;
		if (ft_strchr(st, '\n'))
			break ;
		n = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (buf_checker(&st, n));
}
