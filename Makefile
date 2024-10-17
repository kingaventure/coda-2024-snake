# Makefile

NAME = Snake

SRCS = main.c

all :  $(NAME)

$(NAME): $(SRCS)
	gcc $(SRCS) -o $(NAME) `sdl2-config --cflags --libs` -lSDL2_image
    ##MacOS gcc $(SRCS) -o $(NAME) -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_image

fclean:
	rm -f $(NAME)

re: fclean all