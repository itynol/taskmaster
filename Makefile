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
NAME_SRV = taskmaster
NAME_CLN = client
FLAGS = -Wall -Wextra -Werror

SRCS_DIR=sources
OBJS_DIR=objects

SRV_DIR=server
CLN_DIR=client

SRCS_SRV = main.c get_next_line.c server.c start.c parser.c
SRCS_CLN = client.c help_hendler.c

SOURCES_S=$(addprefix $(SRV_DIR)/, $(SRCS_SRV))
SOURCES_C=$(addprefix $(CLN_DIR)/, $(SRCS_CLN))

OBJS_SRV = $(addprefix $(OBJS_DIR)/, $(SOURCES_S:.c=.o))
OBJS_CLN = $(addprefix $(OBJS_DIR)/, $(SOURCES_C:.c=.o))

INCLUDES = task_master.h

all:	$(NAME)

$(NAME):	$(OBJS_CLN) $(OBJS_SRV)
			@echo "Compilation..."
			@make --directory ./libft
			@gcc -g $(FLAGS) $(OBJS_SRV) -o $(NAME_SRV) -L ./libft -lft 
			@gcc -g $(FLAGS) $(OBJS_CLN) -o $(NAME_CLN) -L ./libft -lft  -lreadline
			@echo "Your ./taskmaster is ready"

$(OBJS_CLN)	:	$(OBJS_DIR)/$(CLN_DIR)/%.o: $(SRCS_DIR)/$(CLN_DIR)/%.c
			@gcc $(FLAGS) -c -g $<  -o $@

$(OBJS_SRV)	:	$(OBJS_DIR)/$(SRV_DIR)/%.o: $(SRCS_DIR)/$(SRV_DIR)/%.c
			@gcc $(FLAGS) -c -g $<  -o $@

clean:
			@echo "\033[34mDeliting o-files\033[34m"
			@/bin/rm -f $(OBJS_CLN) $(OBJS_SRV)
			@make clean --directory ./libft

fclean:	clean
			@echo "\033[34mDeliting binary\033[34m"
			@/bin/rm -f $(NAME_CLN) $(NAME_SRV)
			@make fclean --directory ./libft

re:	fclean all

