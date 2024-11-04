# Makefile

NAME = nom_de_l_executable

SRCS = main.c serpent.c pomme.c

all: $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME) -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf

fclean:
	rm -f $(NAME)

re: fclean all
