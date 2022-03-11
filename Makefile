CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS = main.c cmd.c ft_split.c ft_memcpy.c ft_strncmp.c ft_strlen.c ft_strjoin.c

OBJ = $(SRCS:.c=.o)
RM = rm -f
NAME = pipex

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) pipex.h
	$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(OBJ)

re: fclean all
