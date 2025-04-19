CC = cc
CFLAGS = -Wall -Werror -Wextra -g 
# -fsanitize=address
NAME = cube3d_level_editor
CFILES = srcs/main.c \
\
		srcs/render/draw.c \
		srcs/render/images.c \
		srcs/render/images_utils.c \
		srcs/render/objects.c \
\
		srcs/vector/vector.c \
		srcs/vector/vector_utils.c \


OBJS = ${CFILES:.c=.o}

.c.o:
	${CC} ${CFLAGS} -Iminilibx -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} $(OBJS) -L./lib/libft -lft -L./lib/minilibx -lmlx -L/usr/lib -Iminilibx -lreadline -lXext -lX11 -lm -lz -o $(NAME)

fclean:	clean
	rm -rf ${NAME}

clean:
	rm -rf ${OBJS}

re:	fclean all

.PHONY: all clean fclean re