# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 15:38:42 by heynard           #+#    #+#              #
#    Updated: 2017/06/27 20:26:37 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror

FLAGS_LFT = -L ./libft/ -lft

PATH_SRCS = ./srcs/

SRC_FILES = msh_main.c\
			msh_prompt.c\
			msh_copy_environ.c\
			msh_update_env.c\
			msh_init_env.c\
			msh_parser.c\
			msh_split_spec.c\
			msh_split_quotes.c\
			msh_check_quotes.c\
			msh_replace_var.c\
			msh_handle_line.c\
			msh_handle_command.c\
			msh_builtin_env.c\
			msh_builtin_cd.c\
			msh_builtin_cd_func.c\
			msh_builtin_echo.c\
			msh_builtin_exit.c\
			msh_builtin_setenv.c\
			msh_builtin_unsetenv.c

SRCS = $(addprefix $(PATH_SRCS), $(SRC_FILES))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@$(CC) $(FLAGS) $(FLAGS_LFT) $^ -o $(NAME)
	@echo "\033[1;34mminishell\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJ)
	@echo "\033[1;34mminishell\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft/ fclean
	@rm -f $(NAME)
	@echo "\033[1;34mminishell\t\033[1;33mCleaning minishell\t\033[0;32m[OK]\033[0m"

re: fclean all
