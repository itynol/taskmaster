# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterry <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/11 15:54:02 by jterry            #+#    #+#              #
#    Updated: 2019/07/14 19:32:02 by jterry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = taskmaster
FLAGS = -Wall -Wextra -Werror
SRCS = main.c get_next_line.c server.c start.c parser.c 
OBJS = $(SRCS:.c=.o)


INCLUDES = task_master.h

all:	$(NAME)

$(NAME):	$(OBJS)	
			@echo "\x1b[32;01mCompilation...\x1b[32;01m"
			@make --directory ./libft
			@gcc -g $(FLAGS) $(OBJS) -o $(NAME) -L ./libft -lft -lreadline
			@gcc client.c help_hendler.c -o client -L ./libft -lft  -lreadline
			@echo "\x1b[32;01mYour ./taskmaster is ready\x1b[32;01m"

$(OBJS):	%.o: %.c
			@gcc $(FLAGS) -c -g $< -I $(INCLUDES) -o $@

clean:
			@echo "\033[34mDeliting o-files\033[34m"
			@/bin/rm -f $(OBJS)	
			@make clean --directory ./libft

fclean:	clean
			@echo "\033[34mDeliting binary\033[34m"
			@/bin/rm -f $(NAME)
			@make fclean --directory ./libft

re:	fclean all

