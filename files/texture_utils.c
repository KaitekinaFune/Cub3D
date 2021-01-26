/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:35 by lflint            #+#    #+#             */
/*   Updated: 2021/01/23 19:23:49 by lflint           ###   ########.fr       */
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

int			get_addr(t_txt *txt)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (!(txt[i].addr = mlx_get_data_addr(txt[i].img, &txt[i].bpp,
		&txt[i].lin_l, &txt[i].endian)))
			return (0);
		i++;
	}
	return (1);
}

void		trim_texture(t_txt *txt, t_cub *cub)
{
	char	c;
	int		j;

	j = 0;
	while (j < 5)
	{
		txt[j].i = (j == 4 ? 1 : 2);
		while (cub->file.textures[j][txt[j].i])
		{
			c = cub->file.textures[j][txt[j].i];
			if (c == ' ' || c == '\t')
				txt[j].i += 1;
			else
				break ;
		}
		j++;
	}
}
