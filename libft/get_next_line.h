/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nortolan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:05:39 by nortolan          #+#    #+#             */
/*   Updated: 2021/11/02 12:39:29 by nortolan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1921
# endif

char	*result_line(char **st);
char	*buf_checker(char **st, int n);
char	*get_next_line(int fd);
//size_t	ft_strlen(const char *str);
//char	*ft_strdup(const char *s1);
//size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
//size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
//char	*ft_strjoin(char const *s1, char const *s2);
//char	*ft_strchr(const char *s, int c);
//char	*ft_substr(char const *s, unsigned int start, size_t len);
#endif
