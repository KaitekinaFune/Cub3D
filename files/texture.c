/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:44 by lflint            #+#    #+#             */
/*   Updated: 2021/01/23 19:24:10 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		apply_texture(t_cub *cub, t_txt *txts, t_ray *ray, int x)
{
	int		y;
	int		r;
	char	*txt;
	char	*dst;

	init_txt(ray, cub, txts);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		r = -1;
		txt = NULL;
		dst = cub->mlx.addr + (y * cub->mlx.lin_l + x * (cub->mlx.bpp / 8));
		ray->tex_y = (int)ray->tex_pos & (txts[ray->nswe].height - 1);
		ray->tex_pos += ray->t_step;
		txt = txts[ray->nswe].addr + (ray->tex_x * txts[ray->nswe].lin_l
		+ ray->tex_y * (txts[ray->nswe].bpp / 8));
		while (++r < (txts[ray->nswe].bpp / 8))
			dst[r] = txt[r];
		y++;
	}
	draw_ceil_floor(cub, ray, x);
}

int			open_txts(t_txt *txt, t_cub *cub)
{
	int		j;

	j = 0;
	while (j < 5)
	{
		if (cub->file.toggle[j] == XPM)
		{
			if (!(txt[j].img = mlx_xpm_file_to_image(cub->mlx.mlx,
			&cub->file.textures[j][txt[j].i], &txt[j].width, &txt[j].height)))
				cub_exit(cub, 13);
		}
		else if (cub->file.toggle[j] == PNG)
		{
			if (!(txt[j].img = mlx_png_file_to_image(cub->mlx.mlx,
			&cub->file.textures[j][txt[j].i], &txt[j].width, &txt[j].height)))
				cub_exit(cub, 13);
		}
		j++;
	}
	return (get_addr(txt));
}
