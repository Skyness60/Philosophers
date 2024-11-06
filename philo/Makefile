NAME = philo
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -L./garbage_collector -lgarbage_collector
SRC =	src/philo.c \
		src/init.c \
		src/atoi.c \
		src/threads.c \
		src/utils.c \
		src/check_utils.c \
		src/error.c \
		src/mutex_utils.c \
		src/simulation.c \

OBJECTS = $(SRC:.c=.o)
#################################################################################

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
MAGENTA = '\033[0;35m'
NC = '\033[0m'

#################################################################################


OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME) : $(OBJ)
	@make -C ./garbage_collector --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKLIBS)
	@echo $(BLUE)✅ $@ built! $(NC)

clean:
	@rm -f $(OBJECTS)
	@echo $(YELLOW)🗑️ $(OBJECTS) deleted! $(NC)

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C ./garbage_collector --no-print-directory
	@echo $(RED)🗑️ $(NAME) and $(BONUS) deleted! $(NC)

re: fclean all

.PHONY: re all clean fclean