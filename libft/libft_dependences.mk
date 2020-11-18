# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_dependences.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jterry <jterry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/02 14:28:49 by ggwin-go          #+#    #+#              #
#    Updated: 2019/10/24 18:14:45 by gmelisan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_INCLUDES=-I includes

LIBFT_H_FILES=\
	ft_printf.h\
	ft_string.h\
	ft_vector.h\
	get_next_line.h\
	ft_qsort.h\
	ft_getopt.h\
	libft.h

LIBFT_HEADERS=$(addprefix includes/, $(LIBFT_H_FILES))

LIBFT_SRCS_DIR=sources
LIBFT_OBJS_DIR=objects

LIBFT_MEM_DIR=memory
LIBFT_STR_DIR=string
LIBFT_OUTPUT_DIR=output
FT_PRINTF_DIR=ft_printf
FT_STRING_DIR=ft_string
FT_VECTOR_DIR=ft_vector
LIBFT_LIST_DIR=list
LIBFT_DLIST_DIR=dlist

LIBFT_SRCS_WITHOUT_DIR=\
	get_next_line.c		ft_qsort.c		ft_arr_str_qsort.c\
	ft_getopt.c			ft_abs.c

LIBFT_SRCS_MEM=ft_bzero.c	ft_memalloc.c				ft_memccpy.c\
		ft_memchr.c			ft_memcmp.c					ft_memcpy.c\
		ft_memcpy_rev.c		ft_memdel.c					ft_memmove.c\
		ft_memset.c			ft_realloc.c				ft_swap.c\
		ft_free_ptr_array.c

LIBFT_SRCS_STR=ft_atoi.c	ft_isalnum.c			ft_isalpha.c\
	ft_isascii.c			ft_isdigit.c			ft_isprint.c\
	ft_isspace.c			ft_itoa.c				ft_itoa_base.c\
	ft_sort_str_array.c		ft_strcat.c				ft_strchr.c\
	ft_strclr.c				ft_strcmp.c				ft_strcpy.c\
	ft_strdel.c				ft_strdup.c				ft_strndup.c\
	ft_strequ.c				ft_striter.c\
	ft_striteri.c			ft_strjoin.c			ft_strrejoin.c\
	ft_strlcat.c			ft_strlen.c\
	ft_strmap.c				ft_strmapi.c\
	ft_strncat.c			ft_strncmp.c			ft_strncpy.c\
	ft_strnequ.c			ft_strnew.c				ft_strnstr.c\
	ft_strrchr.c			ft_strsplit.c\
	ft_strstr.c				ft_strsub.c				ft_strtrim.c\
	ft_tolower.c			ft_toupper.c\
	ft_strrejoin.c			ft_atoi_octal.c

LIBFT_SRCS_OUTPUT=ft_putchar.c	ft_putchar_fd.c		ft_putendl.c\
			ft_putendl_fd.c		ft_putnbr.c			ft_putnbr_fd.c\
			ft_putstr.c			ft_putstr_fd.c		ft_putstr_bf.c

SRCS_FT_PRINTF=convert_float.c	convert_integer.c		ft_fdprintf.c\
	ft_printf.c					ft_vfdprintf.c			ft_vprintf.c\
	get_color.c					get_conversion.c		get_flags.c\
	get_length.c				get_precision.c			get_width.c\
	handle_char.c				handle_color.c			handle_conversion.c\
	handle_float.c				handle_integer.c		handle_string.c\
	handle_unknown.c			handle_wchar.c			handle_wstring.c\
	number_to_string.c			number_to_string_e.c	number_to_string_f.c

SRCS_FT_STRING=str_addback.c	str_addfront.c			str_compare.c\
	str_copy.c					str_create.c			str_delarr.c\
	str_delete.c				str_duplicate.c			str_fixlen.c\
	str_get.c					str_insert.c			str_remove.c\
	str_split.c					str_substring.c			str_zero.c\
	str_ncopy.c					str_replace.c

SRCS_FT_VECTOR=vec_addback.c	vec_addfront.c			vec_create.c\
	vec_delete.c				vec_duplicate.c			vec_get.c\
	vec_zero.c

LIBFT_SRCS_LIST=ft_lstadd.c		ft_lstaddback.c			ft_lstdel.c\
	ft_lstdelone.c				ft_lstiter.c			ft_lstmap.c\
	ft_lstnew.c					ft_lstsize.c

LIBFT_SRCS_DLIST=ft_dlstadd.c	ft_dlstaddback.c		ft_dlstdel.c\
	ft_dlstdelend.c				ft_dlstdelfront.c		ft_dlstdelone.c\
	ft_dlstiter.c				ft_dlstnew.c			ft_dlstsize.c\
	ft_dlst2start.c				ft_dlst2end.c

LIBFT_SOURCES=$(LIBFT_SRCS_WITHOUT_DIR)\
	$(addprefix $(LIBFT_MEM_DIR)/, $(LIBFT_SRCS_MEM))\
	$(addprefix $(LIBFT_STR_DIR)/, $(LIBFT_SRCS_STR))\
	$(addprefix $(LIBFT_OUTPUT_DIR)/, $(LIBFT_SRCS_OUTPUT))\
	$(addprefix $(FT_PRINTF_DIR)/, $(SRCS_FT_PRINTF))\
	$(addprefix $(FT_STRING_DIR)/, $(SRCS_FT_STRING))\
	$(addprefix $(FT_VECTOR_DIR)/, $(SRCS_FT_VECTOR))\
	$(addprefix $(LIBFT_LIST_DIR)/, $(LIBFT_SRCS_LIST))\
	$(addprefix $(LIBFT_DLIST_DIR)/, $(LIBFT_SRCS_DLIST))

LIBFT_SRCS=$(addprefix $(LIBFT_SRCS_DIR)/, $(LIBFT_SOURCES))
LIBFT_OBJS=$(addprefix $(LIBFT_OBJS_DIR)/, $(LIBFT_SOURCES:%.c=%.o))

LIBFT_OBJS_CLEAN=$(strip $(foreach f,$(LIBFT_OBJS),$(wildcard $(f))))
