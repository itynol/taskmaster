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

INCLUDES:=\
		-I include \
		-I libft/includes

SRCS_DIR=sources
OBJS_DIR=objects

SRV_DIR=server
CLN_DIR=client

LIBFT_DIR=libft
LIBFT_A=$(LIBFT_DIR)/libft.a

SRCS_SRV = main.c server.c start.c parser.c
SRCS_CLN = client.c help_hendler.c

SOURCES_S=$(addprefix $(SRV_DIR)/, $(SRCS_SRV))
SOURCES_C=$(addprefix $(CLN_DIR)/, $(SRCS_CLN))

OBJS_SRV = $(addprefix $(OBJS_DIR)/, $(SOURCES_S:.c=.o))
OBJS_CLN = $(addprefix $(OBJS_DIR)/, $(SOURCES_C:.c=.o))

all:	$(NAME)

$(NAME):	$(LIBFT_A) obj_subdir $(OBJS_CLN) $(OBJS_SRV)
			@echo "Compilation..."
			@make --directory ./libft
			@gcc -g $(FLAGS) $(INCLUDES) $(LIBFT_A) $(OBJS_SRV) -o $(NAME_SRV) 
			@gcc -g $(FLAGS) $(INCLUDES) $(LIBFT_A) $(OBJS_CLN) -o $(NAME_CLN) -lreadline
			@echo "Your ./taskmaster is ready"

$(OBJS_CLN)	:	$(OBJS_DIR)/$(CLN_DIR)/%.o: $(SRCS_DIR)/$(CLN_DIR)/%.c
			@gcc $(FLAGS) $(INCLUDES) -c -g $<  -o $@ -MMD

$(OBJS_SRV)	:	$(OBJS_DIR)/$(SRV_DIR)/%.o: $(SRCS_DIR)/$(SRV_DIR)/%.c
			@gcc $(FLAGS) $(INCLUDES) -c -g $<  -o $@ -MMD

$(LIBFT_A):
			@make -C $(LIBFT_DIR)

obj_subdir:
		@mkdir -p $(OBJS_DIR)/$(SRV_DIR)
		@mkdir -p $(OBJS_DIR)/$(CLN_DIR)

clean:
			@echo "\033[34mDeliting o-files\033[34m"
			@/bin/rm -rf $(OBJS_DIR)
			@make clean -C $(LIBFT_DIR)
			
fclean:	clean
			@echo "\033[34mDeliting binary\033[34m"
			@/bin/rm -f $(NAME_CLN) $(NAME_SRV)
			@make fclean -C $(LIBFT_DIR)

re:	fclean all

