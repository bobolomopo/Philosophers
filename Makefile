# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jandre <jandre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/02 13:40:06 by jandre            #+#    #+#              #
#    Updated: 2021/07/04 17:32:46 by jandre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LINUXFLAGS = -lpthread
SRC_DIR = sources/
SRCS = philo.c ft_init_mem_val.c ft_init_mutex.c ft_utils.c ft_closing.c \
	ft_routine.c ft_create_thread.c ft_get_time.c ft_check_die.c \
	ft_display_message.c ft_actions.c
SRC =  $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LINUXFLAGS) -I include

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf philo

re: fclean
	make all