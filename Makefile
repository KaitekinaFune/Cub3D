OS		=	$(shell uname)

#mlx library, based on OS
ifeq ($(OS), Linux)
	MLX	= libmlx.a
	MLXDIR	= ./mlx_linux/
	LIBS	= -L . -lmlx -L /usr/include/../lib -lXext -lX11 -lm -lbsd -lz
else
	MLX	= libmlx.dylib
	MLXDIR	= ./mlx/
	LIBS	= -lmlx -Lmlx -framework OpenGL -framework AppKit
	
endif

FLAGS	=	-Wall -Wextra -Werror -g -I .

FIL 	=	cub_bmp_encoder \
			cub_bmp_utils_extra \
			cub_bmp_utils \
			cub_bmp \
			cub_error_utils \
			cub_error \
			cub_exit \
			cub_keys \
			cub_loop_utils \
			cub_loop \
			cub_utils \
			cub3d \
			get_next_line \
			get_next_line_utils \
			map_checker_utils \
			map_checker \
			map_color_utils \
			map_color \
			map_get_utils \
			map_get \
			map_parser_utils \
			map_parser \
			ray_caster_utils \
			ray_caster \
			sprites_utils \
			sprites \
			texture_utils \
			texture

CFL 	= 	$(addprefix files/, $(FIL))

SRC 	=	$(addsuffix .c, $(CFL))

OBJ		=	$(SRC:.c=.o)
HEAD	=	files/cub3d.h

NAME	=	Cub3D

all	:		$(NAME)

$(NAME)	:	$(OBJ) $(MLX)
	$(CC) -g $(FLAGS) -o $(NAME) $(OBJ) $(LIBS)

$(MLX)	:	$(MLX)
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)$(MLX) ./$(MLX)

%.o		: 	%.c $(HEAD)
	$(CC) $(FLAGS) -c -o $@ $<

clean	:
	$(MAKE) clean -C $(MLXDIR)
	rm -rf $(OBJ)

fclean	:	clean
	rm -rf Cub3D $(MLX) *.bmp

re		:	clean all

run		:	$(NAME)
	./$(NAME) maps/map_valid_no_space.cub

bmp		:	$(NAME)
	./$(NAME) maps/map_valid_no_space.cub --save

valgr	:	re
	valgrind --leak-check=full ./$(NAME) maps/map_valid_no_space.cub

val_bmp	:	re
	valgrind --leak-check=full --track-origins=yes ./$(NAME) maps/map_valid_no_space.cub --save