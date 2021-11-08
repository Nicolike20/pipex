/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 18:30:36 by nortolan          #+#    #+#             */
/*   Updated: 2021/09/16 22:15:43 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		res++;
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*aux_itoa(char *res, int len, int n)
{
	while (n > 0)
	{
		res[len--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	len = get_len(n);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len--] = '\0';
	if (n == -2147483648)
	{
		res[len--] = '8';
		n = -214748364;
	}
	if (n == 0)
		res[0] = '0';
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	res = aux_itoa(res, len, n);
	return (res);
}
