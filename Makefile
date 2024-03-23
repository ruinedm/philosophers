CC = cc
FLAGS = 
THREAD_FLAG = -pthread

NAME = philosophers
M_DIR = philo
SRC = $(M_DIR)/philo.c $(M_DIR)/general_utils.c $(M_DIR)/parsing_utils.c $(M_DIR)/conversion_utils.c $(M_DIR)/linked_list_utils.c $(M_DIR)/handle_philos.c
OBJ = $(SRC:.c=.o)
HEADER = $(M_DIR)/philo.h

all: $(NAME)

$(OBJ): $(HEADER)

$(NAME): $(OBJ)
	@($(CC) $(FLAGS) $(THREAD_FLAG) $^ -o $@)
	@echo "Executable linked successfully!"

%.o: %.c
	@($(CC) $(FLAGS) -c $< -o $@)
	@echo "Compiled $<"

clean:
	@(rm -f $(OBJ))
	@echo "Cleaned all object files!"

fclean: clean
	@(rm -f $(NAME))
	@echo "Removed executable succsefully!"
