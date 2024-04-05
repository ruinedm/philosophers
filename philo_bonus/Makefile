CC = cc
FLAGS = -pthread -g

NAME = philo_bonus
SRC = philo.c parsing_utils.c handle_philos.c conversion_utils.c time_utils.c error_and_clear.c ft_itoa.c ft_strjoin.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) -g $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c $(HEADER)
	@($(CC) $(FLAGS) -c -g $< -o $@)
	@echo "Compiled $<"

clean:
	@(rm -f $(OBJ))
	@echo "Cleaned all object files!"

fclean: clean
	@(rm -f $(NAME))
	@echo "Removed executable succsefully!"

re: fclean all