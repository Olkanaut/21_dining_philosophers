NAME		=	philo_three
FLAGS		=	-pthread -g -Wall -Werror -Wextra
HEADERS		=	philo.h

SRC			=	main.c \
				routine.c \
				tools.c \
				tools_stamp.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@gcc $(FLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re:	fclean all

run: all
	./$(NAME) 5 800 200 200

.PHONY: all clean fclean re bonus
