NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = sources/
SRCS = philo.c
SRC =  $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf pipex

re: fclean
	make all