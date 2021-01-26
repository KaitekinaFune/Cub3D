/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:34 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 13:22:15 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		count_height(t_ray *ray, t_cub *cub)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - cub->coords.px + (1 - ray->step_x) / 2)
		/ ray->ray_x;
	else
		ray->wall_dist = (ray->map_y - cub->coords.py + (1 - ray->step_y) / 2)
		/ ray->ray_y;
	ray->lineheight = (int)(cub->mlx.scr_h / ray->wall_dist);
	ray->draw_start = -ray->lineheight / 2 + cub->mlx.scr_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->lineheight / 2 + cub->mlx.scr_h / 2;
	if (ray->draw_end >= cub->mlx.scr_h)
		ray->draw_end = cub->mlx.scr_h - 1;
	if (ray->side == 0)
		ray->wall_x = cub->coords.py + ray->wall_dist * ray->ray_y;
	else
		ray->wall_x = cub->coords.px + ray->wall_dist * ray->ray_x;
	ray->wall_x -= floor(ray->wall_x);
}

void		get_hit(t_ray *ray, t_cub *cub)
{
	while (ray->hit != 1)
	{
		if (ray->x_dist < ray->y_dist)
		{
			if (ray->ray_x <= 1.2f && ray->ray_x >= 0.0f)
				ray->nswe = 2;
			else if (ray->ray_x >= -1.2f && ray->ray_x < 0.0f)
				ray->nswe = 3;
			ray->x_dist += ray->dx_dist;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			if (ray->ray_y >= -1.2f && ray->ray_y < 0.0f)
				ray->nswe = 0;
			else if (ray->ray_y <= 1.2f && ray->ray_y >= 0.0f)
				ray->nswe = 1;
			ray->y_dist += ray->dy_dist;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void		init_ray(t_ray *ray, t_cub *cub, int x)
{
	ray->cam_x = 2.0f * x / (float)cub->mlx.scr_w - 1.0f;
	ray->ray_x = cub->coords.pax + cub->coords.plx * ray->cam_x;
	ray->ray_y = cub->coords.pay + cub->coords.ply * ray->cam_x;
	ray->map_x = (int)cub->coords.px;
	ray->map_y = (int)cub->coords.py;
	ray->hit = 0;
	ray->dx_dist = fabs(1 / ray->ray_x);
	ray->dy_dist = fabs(1 / ray->ray_y);
	get_side(ray, cub);
}

void		image_destroy(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->lin_l = 0;
	mlx->img = NULL;
	mlx->addr = NULL;
}

void		get_side(t_ray *ray, t_cub *cub)
{
	if (ray->ray_x < 0)
	{
		ray->step_x = -1;
		ray->x_dist = (cub->coords.px - ray->map_x) * ray->dx_dist;
	}
	else
	{
		ray->step_x = 1;
		ray->x_dist = (ray->map_x + 1.0f - cub->coords.px) * ray->dx_dist;
	}
	if (ray->ray_y < 0)
	{
		ray->step_y = -1;
		ray->y_dist = (cub->coords.py - ray->map_y) * ray->dy_dist;
	}
	else
	{
		ray->step_y = 1;
		ray->y_dist = (ray->map_y + 1.0f - cub->coords.py) * ray->dy_dist;
	}
}
