NAME = shaderpixel

SRCS = sources/main.cpp\
		sources/WindowApp.cpp\
		sources/ShaderLoader.cpp\
		sources/Player.cpp\

OBJS = $(SRCS:.cpp=.o)

CC = c++

CFLAGS = -g

LDFLAGS = -Iinclude -Llib -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -D GLEW_STATIC

RM = rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: 			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re