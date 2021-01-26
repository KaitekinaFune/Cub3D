/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_loop_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:37:26 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 20:06:28 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_plr_dir_s(t_cub *cub)
{
	if (cub->plr == 'E')
	{
		cub->coords.plx = 0.001;
		cub->coords.ply = -0.66;
		cub->coords.pax = 1.0;
		cub->coords.pay = 0.001;
	}
	else if (cub->plr == 'W')
	{
		cub->coords.plx = 0.001;
		cub->coords.ply = 0.66;
		cub->coords.pax = -1.0;
		cub->coords.pay = 0.001;
	}
}

void		get_plr_dir(t_cub *cub)
{
	if (cub->plr == 'N')
	{
		cub->coords.plx = -0.66;
		cub->coords.ply = 0.001;
		cub->coords.pax = 0.001;
		cub->coords.pay = -1.0;
	}
	else if (cub->plr == 'S')
	{
		cub->coords.plx = 0.66;
		cub->coords.ply = 0.001;
		cub->coords.pax = 0.001;
		cub->coords.pay = 1.0;
	}
	get_plr_dir_s(cub);
}

static int	is_plr(char c)
{
	return (c == 'N' || c == 'W' || c == 'E' || c == 'S');
}

void		get_plr_coords(t_cub *cub)
{
	int		i;
	int		j;
	int		plr_count;

	plr_count = 0;
	i = 0;
	while (cub->map[i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (is_plr(cub->map[i][j]))
			{
				cub->coords.px = j + 0.5f;
				cub->coords.py = i + 0.5f;
				cub->plr = cub->map[i][j];
				plr_count++;
			}
		}
		i++;
	}
	if (plr_count == 1)
		return ;
	cub_error(23, cub, "Wrong player count\n");
}

void		my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->mlx.addr + (y * cub->mlx.lin_l
	+ x * (cub->mlx.bpp / 8));
	*(unsigned int*)dst = color;
}
