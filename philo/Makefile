CC = cc
FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo
M_DIR = philo
SRC = philo.c  parsing_utils.c conversion_utils.c handle_philos.c time_utils.c printing_utils.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

all: $(NAME)

$(OBJ): $(HEADER)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) -g $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c
	@($(CC) $(FLAGS) -c -g $< -o $@)
	@echo "Compiled $<"

clean:
	@(rm -f $(OBJ))
	@echo "Cleaned all object files!"

fclean: clean
	@(rm -f $(NAME))
	@echo "Removed executable succsefully!"

re: fclean all