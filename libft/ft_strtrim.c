/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:23:20 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/18 19:15:28 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		l;
	int		r;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	l = 0;
	r = ft_strlen(s1);
	while (check_set(s1[l], set) == 1)
		l++;
	if (l == r)
	{
		res = (ft_strdup(""));
		if (res == NULL)
			return (NULL);
		else
			return (res);
	}
	while (check_set(s1[r - 1], set))
		r--;
	res = ft_substr(s1, l, r - l);
	return (res);
}
