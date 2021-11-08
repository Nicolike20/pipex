/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 22:51:24 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/18 22:59:43 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *s, char c)
{
	int	t_words;

	t_words = 0;
	while (*s)
	{
		while (*s != c && *s)
			s++;
		t_words++;
		while (*s == c && *s)
			s++;
	}
	return (t_words);
}

static int	char_count(char *s, char c)
{
	int	total;

	total = 0;
	while (*s != c && *s++)
		total++;
	return (total);
}

static int	word_fill(char **tab, char *s, char c, int totalw)
{
	int	i;
	int	j;
	int	cc;

	i = -1;
	while (++i < totalw)
	{
		j = 0;
		cc = char_count(s, c);
		tab[i] = (char *)malloc(sizeof(char) * (cc + 1));
		if (!tab[i])
		{
			while (--i >= 0)
				free(tab[i]);
			free(tab);
			return (1);
		}
		while (*s != c && *s)
			tab[i][j++] = *s++;
		tab[i][j] = '\0';
		while (*s == c && *s)
			s++;
	}
	tab[totalw] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		totalw;
	char	**res;

	if (!s)
		return (NULL);
	while (*s && *s == c)
		s++;
	totalw = word_count((char *) s, c);
	res = (char **)malloc(sizeof(char *) * (totalw + 1));
	if (!res)
	{
		return (NULL);
	}
	if (word_fill(res, (char *) s, c, totalw))
	{
		return (NULL);
	}
	return (res);
}
