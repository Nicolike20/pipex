# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nortolan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/15 11:05:23 by nortolan          #+#    #+#              #
#    Updated: 2021/10/28 15:26:53 by nortolan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

ARFLAGS = -rcs

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c \
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		 ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		 ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

SRCS_GNL = get_next_line.c

OBJS_GNL = $(SRCS_GNL:%.c=%.o)
OBJS_B = $(SRCS_B:%.c=%.o)
OBJS = $(SRCS:%.c=%.o)

.PHONY = all clean fclean re bonus gnl

all: $(NAME)

$(NAME): $(OBJS)
	ar $(ARFLAGS) $@ $?

bonus: $(OBJS_B)
	ar $(ARFLAGS) $(NAME) $?

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

gnl: $(OBJS_GNL)
	ar $(ARFLAGS) $(NAME) $?

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJS_B)
	rm -rf $(OBJS_GNL)

fclean: clean
	rm -rf $(NAME)

re: fclean all
