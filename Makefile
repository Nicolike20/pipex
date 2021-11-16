# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nortolan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 16:33:39 by nortolan          #+#    #+#              #
#    Updated: 2021/11/15 18:42:42 by nortolan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LFT = libft.a
LFT_DIR = libft

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread

SRCS = pipex.c parse.c here_doc.c

OBJS = $(SRCS:%.c=%.o)

.PHONY = all sanitize clean fclean re

all: $(NAME)

sanitize: CFLAGS += -fsanitize=address -g3
sanitize: $(NAME)

$(NAME): $(OBJS) $(LFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT)

$(LFT): $(LFT_DIR)/$(LFT)
	cp $(LFT_DIR)/$(LFT) $(LFT)
$(LFT_DIR)/$(LFT):
	make -sC $(LFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -sC $(LFT_DIR)
	rm -rf $(LFT)
	rm -rf $(OBJS)

fclean: clean
	make fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

re: fclean all
