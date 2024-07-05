CC = cc
FLAGS = -pthread 

NAME = philo
SRC = init_philo.c conversion_utils.c error_and_clear.c observer_of_all.c parser.c parsing_utils.c philo.c printing_utils.c time_utils.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c $(HEADER)
	@($(CC) $(FLAGS) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@(rm -f $(OBJ))
	@echo "Cleaned all object files!"

fclean: clean
	@(rm -f $(NAME))
	@echo "Removed executable succsefully!"

re: fclean all