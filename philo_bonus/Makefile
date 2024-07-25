CC = cc
FLAGS = -Wall -Wextra -Werror
NAME = philo_bonus
SRC = philo.c parsing_utils.c observer_of_all.c handle_philos.c conversion_utils.c philo_helpers.c other_utils.c general_utils.c ft_itoa.c ft_strjoin.c
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