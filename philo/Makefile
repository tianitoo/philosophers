NAME = philo
CC = cc 
FLAGS = -Wall -Werror -Wextra
AR = ar -r
RM = rm -f
HEAD = philo.h
MK = make

SRC = philo_thread.c\
		ft_atoi.c\
		utils.c\
		init.c\
		philo.c\
		ft_isdigit.c\
		eat.c\
		free.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) main.c
	$(CC) main.c $(OBJ) -o $(NAME) $(FLAGS)

%.o : %.c $(HEAD)
	$(CC) -c $< -o $@ $(FLAGS)
clean:
		$(RM) $(OBJ)
		$(RM) main.o

fclean: clean
	$(RM) $(NAME)
	

re: fclean all

.PHONY: all bonus clean fclean re