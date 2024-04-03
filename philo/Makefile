CC = cc
FLAGS = -pthread -g

NAME = philo
SRC = philo.c  parsing_utils.c conversion_utils.c handle_philos.c time_utils.c printing_utils.c observer_of_all.c error_and_clear.c
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