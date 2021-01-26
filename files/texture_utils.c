/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:35 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 01:45:20 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_txt(t_ray *ray, t_cub *cub, t_txt *txts)
{
	ray->tex_x = (int)(ray->wall_x * (float)txts[ray->nswe].width);
	if (ray->side == 0 && ray->ray_x > 0)
		ray->tex_x = txts[ray->nswe].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_y < 0)
		ray->tex_x = txts[ray->nswe].width - ray->tex_x - 1;
	ray->t_step = 1.0f * txts[ray->nswe].height / ray->lineheight;
	ray->tex_pos = (ray->draw_start - cub->mlx.scr_h / 2 + ray->lineheight / 2)
	* ray->t_step;
}

void		get_addr(t_txt *txt, t_cub *cub)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (!(txt[i].addr = mlx_get_data_addr(txt[i].img, &txt[i].bpp,
		&txt[i].lin_l, &txt[i].endian)))
			cub_error(i + 18, cub, "Couldn't get address for texture\n");
		i++;
	}
}
