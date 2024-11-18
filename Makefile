NAME = shaderpixel

SRCS = sources/main.cpp\
		sources/WindowApp.cpp\
		sources/ShaderLoader.cpp\
		sources/Player.cpp\
		sources/Object.cpp\

OBJS = $(SRCS:.cpp=.o)

CC = c++

CFLAGS = -g

LDFLAGS = -Iinclude -Llib -lglfw -lGLEW -lGL -lX11 -lpthread -lXrandr -lXi -ldl -D GLEW_STATIC

RM = rm -f

all:			image_load $(NAME)

image_load:
	if [ ! -f headers/stb_image.h ]; then \
		git clone https://github.com/nothings/stb.git; \
		cp stb/stb_image.h headers; \
		rm -rf stb; \
	fi

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: 			%.cpp
				$(CC) $(CFLAGS) -c $< -o $@
				
clean:
			$(RM) $(OBJS)
			
fclean:		clean
			$(RM) headers/stb_image.h
			$(RM) $(NAME)
			
re:			fclean all

.PHONY:		all clean fclean re