/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:33:19 by lflint            #+#    #+#             */
/*   Updated: 2021/01/23 19:23:18 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_sprite(t_cub *cub, int i, t_spr_r *spr)
{
	spr->x = cub->sprites[i].x - cub->coords.px + 0.5f;
	spr->y = cub->sprites[i].y - cub->coords.py + 0.5f;
	spr->inv = 1.0f / (cub->coords.plx * cub->coords.pay - cub->coords.pax *
	cub->coords.ply);
	spr->tr_x = spr->inv * (cub->coords.pay * spr->x - cub->coords.pax *
	spr->y);
	spr->tr_y = spr->inv * (-cub->coords.ply * spr->x + (cub->coords.plx *
	spr->y));
	spr->scr_x = (int)((cub->mlx.scr_w / 2) * (1 + spr->tr_x / spr->tr_y));
	spr->h = abs((int)(cub->mlx.scr_h / (spr->tr_y)));
	spr->ds_y = -spr->h / 2 + cub->mlx.scr_h / 2;
	if (spr->ds_y < 0)
		spr->ds_y = 0;
	spr->de_y = spr->h / 2 + cub->mlx.scr_h / 2;
	if (spr->de_y >= cub->mlx.scr_h)
		spr->de_y = cub->mlx.scr_h - 1;
	spr->w = abs((int)(cub->mlx.scr_h / (spr->tr_y)));
	spr->ds_x = -spr->w / 2 + spr->scr_x;
	if (spr->ds_x < 0)
		spr->ds_x = 0;
	spr->de_x = spr->w / 2 + spr->scr_x;
	if (spr->de_x >= cub->mlx.scr_w)
		spr->de_x = cub->mlx.scr_w - 2;
}

void		cast_sprite(t_cub *cub, t_txt *txts, float *z_buffer, t_spr_r *spr)
{
	int		y;

	y = spr->ds_y - 1;
	spr->tex_x = (int)(256 * (spr->stripe - (-spr->w / 2 + spr->scr_x)) *
	txts[4].height / spr->w) / 256;
	if (spr->tr_y > 0 && spr->stripe > 0 && spr->stripe < cub->mlx.scr_w &&
	spr->tr_y < z_buffer[spr->stripe])
		while (++y < spr->de_y)
		{
			spr->d = (y) * 256 - cub->mlx.scr_h * 128 + spr->h * 128;
			spr->tex_y = ((spr->d * txts[4].height) / spr->h) / 256;
			spr->txt = txts[4].addr + (spr->tex_y * txts[4].lin_l
			+ spr->tex_x * (txts[4].bpp / 8));
			spr->dst = cub->mlx.addr + (y * cub->mlx.lin_l + spr->stripe *
			(cub->mlx.bpp / 8));
			if (*spr->txt)
			{
				spr->r = -1;
				while (++spr->r < (txts[4].bpp / 8))
					spr->dst[spr->r] = spr->txt[spr->r];
			}
		}
}

void		cast_sprites(t_cub *cub, t_txt *txts, float *z_buffer)
{
	int		i;
	t_spr_r	*spr;

	i = -1;
	count_sort_sprites(cub);
	while (++i < cub->sprite_count)
	{
		if (!(spr = malloc(sizeof(t_spr_r))))
			cub_error(14, cub, "Insufficient memory\n");
		init_sprite(cub, i, spr);
		spr->stripe = spr->ds_x - 1;
		while (++spr->stripe < spr->de_x)
			cast_sprite(cub, txts, z_buffer, spr);
		free(spr);
	}
}
