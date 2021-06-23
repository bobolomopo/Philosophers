NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = sources/
SRCS = philo.c ft_atol.c ft_isdigit.c ft_strlen.c ft_init_struc.c \
	ft_get_time.c ft_routine.c ft_utils.c
SRC =  $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf philo

re: fclean
	make all