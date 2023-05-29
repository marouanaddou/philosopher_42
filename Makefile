CC = cc
CFLAGC = -Wall -Wextra -Werror #-fsanitize=thread -g
RM = rm -rf
SRC =  ft_atoi.c  check_error.c main.c data_philo.c philo_utils.c philo.c
THREAD = -pthread
OBJ = $(SRC:.c=.o) 
NAME = philo 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(THREAD) $(CFLAGC) $(OBJ) -o $@
%.o : %.c
	$(CC) $(THREAD) -Wall -Wextra -Werror -c $^ -o $@

clean :
	$(RM) $(OBJ) 
fclean : clean
	$(RM) $(NAME)
re : fclean all

