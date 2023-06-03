NAME = philo
CC = cc 
FLAGS = -Wall -Werror -Wextra -fsanitize=thread -g
AR = ar -r
RM = rm -f
HEAD = philo.h
MK = make
PRINTF = ./ft_printf/ft_printf.a
HEADPRINTF = ./ft_printf/ft_printf.h



PRINTFSRC = ./ft_printf/ft_printf.c\
		./ft_printf/ft_putchar.c\
		./ft_printf/ft_puthex.c\
		./ft_printf/ft_putnbr.c\
		./ft_printf/ft_putstr.c\
		./ft_printf/ft_putunsignednbr.c\
		./ft_printf/ft_printf.h

SRC = philo_thread.c\
		ft_atoi.c\
		utils.c\
		init.c\
		philo.c\
		ft_isdigit.c\



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(PRINTF): $(PRINTFSRC)
	$(MK) -C ./ft_printf

$(NAME): $(PRINTF) $(OBJ) main.c
	$(CC) main.c $(PRINTF) $(OBJ) -o $(NAME) $(FLAGS)

%.o : %.c $(HEAD)
	$(CC) -Wall -Wextra -Werror -c $< -o $@
clean:
		$(RM) $(OBJ)
		$(RM) main.o
		$(MK) clean -C ./ft_printf

fclean: clean
	$(RM) $(NAME)
	$(RM) $(PRINTF)
	

re: fclean all

.PHONY: all bonus clean fclean re