CC = cc
FLAGS = -fsanitize=thread
THREAD_FLAG = -pthread

NAME = philosophers
M_DIR = philo
SRC = $(M_DIR)/philo.c $(M_DIR)/general_utils.c $(M_DIR)/parsing_utils.c $(M_DIR)/conversion_utils.c $(M_DIR)/handle_philos.c $(M_DIR)/time_utils.c
OBJ = $(SRC:.c=.o)
HEADER = $(M_DIR)/philo.h

all: $(NAME)

$(OBJ): $(HEADER)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) $(THREAD_FLAG) -g $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c
	@($(CC) $(FLAGS) $(THREAD_FLAG) -c -g $< -o $@)
	@echo "Compiled $<"

clean:
	@(rm -f $(OBJ))
	@echo "Cleaned all object files!"

fclean: clean
	@(rm -f $(NAME))
	@echo "Removed executable succsefully!"

re: fclean all