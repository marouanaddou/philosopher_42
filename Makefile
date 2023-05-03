CC = cc
f =  -fsanitize=thread -g
CFLAGC = -Wall -Wextra -Werror
RM = rm -rf
SRC = libft.c philosopher.c main.c data_philo.c philo_utils.c
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

