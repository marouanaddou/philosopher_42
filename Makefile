CC = GCC
#f =  -fsanitize=thread -g
CFLAGC = -Wall -Wextra -Werror
RM = rm -rf
SRC = libft.c philosopher.c main.c data_philo.c 

OBJ = $(SRC:.c=.o) 
NAME = philo 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC)  $(CFLAGC) $(OBJ) -o $@
%.o : %.c
	$(CC)  -Wall -Wextra -Werror -c $^ -o $@

clean :
	$(RM) $(OBJ) 
fclean : clean
	$(RM) $(NAME)
re : fclean all

