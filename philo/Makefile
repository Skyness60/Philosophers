NAME = philo

CC = cc -g3

SOURCES =	srcs/philo.c \
			srcs/parsing/parse_arguments.c \
			srcs/utils/mutex/mutex_utils.c \
			srcs/utils/notlibft/ft_isspace.c \
			srcs/utils/notlibft/ft_atoi.c \

OBJECTS = $(SOURCES:.c=.o)

FLAGS = -Wall -Wextra -Werror
OPTIONS = -c

#################################################################################

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
NC = '\033[0m'

#################################################################################

%.o: %.c
	@$(CC) $(FLAGS) $(OPTIONS) $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo $(BLUE)✅ $@ built! $(NC)

all: $(NAME)

clean:
	@rm -f $(OBJECTS)
	@echo $(YELLOW)🗑️ $(OBJECTS) deleted! $(NC)

fclean: clean
	@rm -f $(NAME)
	@echo $(RED)🗑️ $(NAME) deleted! $(NC)

re: fclean all

.PHONY: all clean fclean re
