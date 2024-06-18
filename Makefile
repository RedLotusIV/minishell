# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 22:18:52 by amouhand          #+#    #+#              #
#    Updated: 2024/06/18 16:03:19 by amouhand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft.a

CC = cc

CFLAGS = -Wall -Wextra

SPECIALFLAGS = -lreadline -lhistory

SRC =	src/main.c src/utils/cmd_utils.c src/parser/parser_utils.c src/parser/parser.c\
		src/lexer/lexer.c src/lexer/lexer_utils.c src/parser/parser_tree.c\
		src/parser/parser_cmd.c src/parser/parser_cmd_utils.c src/parser/parsing_error.c\
		src/utils/parsing_utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(SPECIALFLAGS) $(OBJ) -g -Llibft -lft -o $(NAME)

$(LIBFT):
	@make -s -C libft

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