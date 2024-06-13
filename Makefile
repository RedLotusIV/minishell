# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 22:18:52 by amouhand          #+#    #+#              #
#    Updated: 2024/06/13 00:39:09 by amouhand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CC = cc

CFLAGS = -Wall -Wextra

SPECIALFLAGS = -lreadline -lhistory

SRC =	src/main.c src/utils/utils.c src/parser/parser_utils.c src/parser/parser.c\
		src/lexer/lexer.c src/lexer/lexer_utils.c src/parser/parser_tree.c\

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(SPECIALFLAGS) $(OBJ) -g -Llibft -lft -o $(NAME)

$(LIBFT):
	@make -C libft

%.o : %.c
	@$(CC) $(CFLAGS) -g -c $< -o $@

clean:
	@make clean -s -C libft
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C libft

re: fclean all

clear: all clean

.PHONY: all clean fclean re