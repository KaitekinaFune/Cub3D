/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:31 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 15:54:01 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "mlx/mlx.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define MS 0.08f
# define RS 0.06f

# define PNG	2
# define XPM	1

# ifdef __linux__
#  define K_ESC		65307
#  define K_LEFT		65361
#  define K_RIGHT	65363
#  define K_W		119
#  define K_S		115
#  define K_A		97
#  define K_D		100
#  define MAXRESW	1920
#  define MAXRESH	1080
# else
#  define K_ESC		53
#  define K_LEFT		123
#  define K_RIGHT	124
#  define K_W		13
#  define K_S		1
#  define K_A		0
#  define K_D		2
#  define MAXRESW	1440
#  define MAXRESH	900
# endif

# define W			0
# define S			1
# define LEFT		2
# define RIGHT		3
# define A			4
# define D			5
# define ESC		6
# define KEYSIZE	7

# define KEYPRESS 	2
# define KEYRELEASE	3

# define BUFFER_SIZE 256

void	ft_strdel(char **as);

typedef struct	s_coords
{
	float		px;
	float		py;
	float		pax;
	float		pay;
	float		plx;
	float		ply;
}				t_coords;

typedef struct	s_buffer
{
	int			length;
	char		*data;
}				t_buf;

typedef struct	s_t_buf
{
	int			toggle;
	int			i;
	int			fd;
	char		*temp;
}				t_t_buf;

typedef struct	s_txt
{
	int			width;
	int			height;
	int			bpp;
	int			lin_l;
	int			endian;
	char		*addr;
	void		*img;
	int			i;
}				t_txt;

typedef struct	s_sprite
{
	float		x;
	float		cx;
	float		y;
	float		cy;
	float		dist;
}				t_sprite;

typedef struct	s_spr_r
{
	float		x;
	float		y;
	float		inv;
	float		tr_x;
	float		tr_y;
	char		*txt;
	char		*dst;
	int			scr_x;
	int			h;
	int			w;
	int			ds_x;
	int			de_x;
	int			ds_y;
	int			de_y;
	int			tex_y;
	int			tex_x;
	int			d;
	int			stripe;
	int			wy;
	int			r;
}				t_spr_r;

typedef struct	s_ray
{
	float		cam_x;
	float		ray_x;
	float		ray_y;
	float		x_dist;
	float		y_dist;
	float		dx_dist;
	float		dy_dist;
	float		wall_dist;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	int			lineheight;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	float		t_step;
	float		tex_pos;
	int			nswe;
	int			side;
	int			hit;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct	s_mlx
{
	void		*img;
	void		*mlx;
	void		*win;
	void		*addr;
	int			scale;
	int			bpp;
	int			lin_l;
	int			endian;
	int			scr_w;
	int			scr_scale;
	int			scr_h;
	int			plr_scale;
}				t_mlx;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_file
{
	char		*textures[5];
	int			toggle[5];
	char		*colors[2];
	int			f_rgb;
	int			c_rgb;
	int			dot;
	int			chars;
	int			i;
	int			count;
	char		plr;
	int			space;
}				t_file;

typedef struct	s_cub
{
	t_file		file;
	t_mlx		mlx;
	t_txt		txt[5];
	t_coords	coords;
	t_sprite	*sprites;
	int			key[KEYSIZE];
	int			sprite_count;
	int			sprite_num;
	char		**map;
	char		plr;
}				t_cub;

typedef struct	s_gnl
{
	int			done;
	int			reach;
	size_t		bytes;
	size_t		buf_size;
	size_t		line_length;
	char		*line;
	char		buf[BUFFER_SIZE];
}				t_gnl;

typedef struct	s_bmp_head
{
	char		*flag;
	int			reserved;
	int			offset;
	int			file_size;
	int			planes;
	int			bit_per_pixel;
	int			compress;
	int			hr;
	int			vr;
	int			colors;
	int			important_color;
}				t_bmp_head;

typedef struct	s_bmp_encode
{
	char		*buf;
	int			width;
	int			height;
	int			extra_bytes;
	int			rgb_size;
	int			header_info_size;
	t_bmp_head	head;
	size_t		row_bytes;
	size_t		buf_bytes;
}				t_bmp_encode;

typedef struct	s_vec
{
	int			x;
	int			y;
}				t_vec;

/*
** cub_bmp_encoder.c
*/
void			bmp_image_data(t_bmp_encode *encoder, t_buf *buf, int pos);
int				buf_uint32(t_buf *buf, unsigned int value, int offset);
int				buf_uint16(t_buf *buf, unsigned int value, int offset);
int				buf_int32(t_buf *buf, int value, int offset);
/*
** cub_bmp_utils_extra.c
*/
char			buf_ascii_map(unsigned int index, char c);
t_buf			*buf_create(int length);
void			buf_destroy(t_buf **buf_ptr);
int				buf_poops(t_buf *buf, unsigned char *s, int offset, int len);

/*
** cub_bmp_utils.c
*/
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			bmp_init_encode(t_bmp_encode *encoder, t_cub *cub);
void			bmp_init_head(t_bmp_encode *encoder);
int				bmp_bitshift(int x, int n);
void			buf_fill(t_buf *buf, unsigned char value, int start, int end);

/*
** cub_bmp.c
*/
int				buf_ascii(t_buf *buf, char *s, int offset, int length);
int				bmp_encode_head(t_bmp_encode *encoder, t_buf *buf);
int				cub_bmp(t_cub *cub);

/*
** cub_error_utils.c
*/
void			free_colors(t_cub *cub, int err);
void			free_textures_extra(t_cub *cub, int err);
void			free_textures(t_cub *cub, int err);

/*
** cub_error.c
*/
void			cub_error(int err_num, t_cub *cub, char *err);
void			file_error(t_cub *cub, int mode, char *line);

/*
** cub_exit.c
*/
void			free_map(t_cub *cub);
int				catch_cross(t_cub *cub);
void			cub_exit(t_cub *cub, int i);

/*
** cub_keys.c
*/
void			key_vert(t_cub *cub);
void			key_side(t_cub *cub);
void			key_hori(t_cub *cub);
int				ft_key_release(int keycode, t_cub *cub);
int				ft_key_hit(int keycode, t_cub *cub);

/*
** cub_loop_utils.c
*/
void			get_plr_coords(t_cub *cub);
void			get_plr_dir(t_cub *cub);
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);

/*
** cub_loop.c
*/
void			cub_loop(t_cub *cub);
void			cub_init(t_cub *cub, int mode);
void			new_image(t_cub *cub);

/*
** cub_utils.c
*/
size_t			ft_strlen(const char *s);
int				empty_line(char *line);
int				ft_core(t_cub *cub);
char			*ft_strdup(const char *s1);
void			*ft_memmove(void *dst, const void *src, size_t len);

/*
** get_next_line.c
*/
int				get_next_line(int fd, char **line);

/*
** get_next_line_utils.c
*/
void			ft_bzero(void *s, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);

/*
** map_checker_utils.c
*/
int				check_sp_vert(t_cub *cub, int i, int j);
int				check_sp_hori(t_cub *cub, int i, int j);

/*
** map_checker.c
*/
int				map_content(t_cub *cub);
int				map_holes(t_cub *cub);

/*
** map_color_utils.c
*/
void			check_txt_type(t_cub *cub);
void			check_textures(t_cub *cub);
int				is_color(char c);
int				is_digit(char c);
int				get_begin(char *str);

/*
** map_color.c
*/
void			check_colors(t_cub *cub);

/*
** map_get_utils.c
*/
int				is_map(char c);
int				before_map(t_cub *cub);
int				during_map(t_cub *cub, int *i);
int				after_map(t_cub *cub, int *i);
int				skip_args(t_cub *cub);

/*
** map_get.c
*/
int				get_map(t_cub *cub, char *map_name);

/*
** map_parser_utils.c
*/
void			resol_mode(char *line, t_cub *cub, int mode);
int				check_line(char *line);
void			skip_ws(char *line, int *j);
int				check_ext(char *name, char *check);
int				ft_strchr(char *str, char c1, char c2);

/*
** map_parser.c
*/
int				parse_resol(char *line, t_cub *cub);
void			get_file(t_cub *cub, char *map_name);

/*
** ray_caster_utils.c
*/
void			count_height(t_ray *ray, t_cub *cub);
void			get_hit(t_ray *ray, t_cub *cub);
void			init_ray(t_ray *ray, t_cub *cub, int x);
void			image_destroy(t_mlx *mlx);
void			get_side(t_ray *ray, t_cub *cub);

/*
** ray_caster.c
*/
void			cast_rays(t_ray *ray, t_cub *cub, int x);
int				count_rays(t_cub *cub, t_txt *txts);
void			draw_ceil_floor(t_cub *cub, t_ray *ray, int x);

/*
** sprites_utils.c
*/
void			sort_sprites(t_cub *cub);
int				count_sprites(t_cub *cub);
void			count_sort_sprites(t_cub *cub);
void			get_sprites(t_cub *cub);

/*
** sprites.c
*/
void			init_sprite(t_cub *cub, int i, t_spr_r *spr);
void			cast_sprite(t_cub *cub, t_txt *txts, float *z_buffer,
t_spr_r *spr);
void			cast_sprites(t_cub *cub, t_txt *txts, float *z_buffer);

/*
** texture_utils.c
*/
void			init_txt(t_ray *ray, t_cub *cub, t_txt *txts);
void			get_addr(t_txt *txt, t_cub *cub);

/*
** texture.c
*/
void			apply_texture(t_cub *cub, t_txt *txts, t_ray *ray, int x);
void			open_txts(t_txt *txt, t_cub *cub);

#endif
