/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:51:29 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:04:12 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		cub_loop(t_cub *cub)
{
	mlx_hook(cub->mlx.win, KEYPRESS, (1L << 0), &ft_key_hit, cub);
	mlx_hook(cub->mlx.win, KEYRELEASE, (1L << 1), &ft_key_release, cub);
	mlx_hook(cub->mlx.win, 17, 0, &catch_cross, cub);
	mlx_loop_hook(cub->mlx.mlx, ft_core, cub);
	mlx_loop(cub->mlx.mlx);
}

void		new_image(t_cub *cub)
{
	cub->mlx.img = mlx_new_image(cub->mlx.mlx, cub->mlx.scr_w, cub->mlx.scr_h);
	cub->mlx.addr = mlx_get_data_addr(cub->mlx.img, &cub->mlx.bpp,
	&cub->mlx.lin_l, &cub->mlx.endian);
}

void		cub_init(t_cub *cub, int mode)
{
	get_plr_coords(cub);
	get_plr_dir(cub);
	cub->mlx.mlx = mlx_init();
	open_txts(cub->txt, cub);
	if (mode == 0)
		cub->mlx.win = mlx_new_window(cub->mlx.mlx, cub->mlx.scr_w,
		cub->mlx.scr_h, "Cub3D");
	if (count_sprites(cub) > 0)
		get_sprites(cub);
	count_rays(cub, cub->txt);
	if (mode == 0)
	{
		mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
		cub_loop(cub);
	}
	else
	{
		cub_bmp(cub);
		cub_exit(cub, 2);
	}
}
