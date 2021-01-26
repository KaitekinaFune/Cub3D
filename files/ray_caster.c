/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:24:45 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 01:48:25 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		cast_rays(t_ray *ray, t_cub *cub, int x)
{
	init_ray(ray, cub, x);
	get_hit(ray, cub);
	count_height(ray, cub);
}

int			count_rays(t_cub *cub, t_txt *txts)
{
	t_ray	*ray;
	int		x;
	float	*z_buffer;

	if (!(z_buffer = malloc(sizeof(float) * cub->mlx.scr_w)))
		cub_error(24, cub, "Insufficient memory\n");
	x = 0;
	new_image(cub);
	while (x < cub->mlx.scr_w)
	{
		if (!(ray = malloc(sizeof(*ray))))
		{
			free(z_buffer);
			cub_error(24, cub, "Insufficient memory\n");
		}
		cast_rays(ray, cub, x);
		z_buffer[x] = ray->wall_dist;
		apply_texture(cub, txts, ray, x);
		free(ray);
		x++;
	}
	if (cub->sprite_count > 0)
		cast_sprites(cub, txts, z_buffer);
	free(z_buffer);
	return (1);
}

void		draw_ceil_floor(t_cub *cub, t_ray *ray, int x)
{
	int		y;

	y = -1;
	while (++y < ray->draw_start)
		my_mlx_pixel_put(cub, x, y, cub->file.c_rgb);
	y = ray->draw_end - 1;
	while (++y < cub->mlx.scr_h)
		my_mlx_pixel_put(cub, x, y, cub->file.f_rgb);
}
