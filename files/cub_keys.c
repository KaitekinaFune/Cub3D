/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:52:14 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 13:22:15 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		key_vert(t_cub *cub)
{
	char	cx;
	char	cy;

	if (cub->key[W])
	{
		cy = cub->map[(int)(cub->coords.py + cub->coords.pay * MS)]
		[(int)(cub->coords.px)];
		cx = cub->map[(int)cub->coords.py]
		[(int)(cub->coords.px + cub->coords.pax * MS)];
		if (cy != '1' && cy != '2')
			cub->coords.py += cub->coords.pay * MS;
		if (cx != '1' && cx != '2')
			cub->coords.px += cub->coords.pax * MS;
	}
	if (cub->key[S])
	{
		cy = cub->map[(int)(cub->coords.py - cub->coords.pay * MS)]
		[(int)cub->coords.px];
		cx = cub->map[(int)cub->coords.py]
		[(int)(cub->coords.px - cub->coords.pax * MS)];
		if (cx != '1' && cx != '2')
			cub->coords.px -= cub->coords.pax * MS;
		if (cy != '1' && cy != '2')
			cub->coords.py -= cub->coords.pay * MS;
	}
}

void		key_side(t_cub *cub)
{
	char	cx;
	char	cy;

	if (cub->key[D])
	{
		cy = cub->map[(int)(cub->coords.py + cub->coords.ply * MS)][(int)
		(cub->coords.px)];
		cx = cub->map[(int)cub->coords.py]
		[(int)(cub->coords.px + cub->coords.plx * MS)];
		if (cy != '1' && cy != '2')
			cub->coords.py += cub->coords.ply * MS;
		if (cx != '1' && cx != '2')
			cub->coords.px += cub->coords.plx * MS;
	}
	if (cub->key[A])
	{
		cy = cub->map[(int)(cub->coords.py - cub->coords.ply * MS)]
		[(int)cub->coords.px];
		cx = cub->map[(int)cub->coords.py]
		[(int)(cub->coords.px - cub->coords.plx * MS)];
		if (cx != '1' && cx != '2')
			cub->coords.px -= cub->coords.plx * MS;
		if (cy != '1' && cy != '2')
			cub->coords.py -= cub->coords.ply * MS;
	}
}

void		key_hori(t_cub *cub)
{
	float	pax;
	float	pay;

	if (cub->key[RIGHT])
	{
		pax = cub->coords.pax;
		cub->coords.pax = cub->coords.pax * cos(-RS)
		- cub->coords.pay * sin(-RS);
		cub->coords.pay = pax * sin(-RS) + cub->coords.pay * cos(-RS);
		pay = cub->coords.plx;
		cub->coords.plx = cub->coords.plx * cos(-RS)
		- cub->coords.ply * sin(-RS);
		cub->coords.ply = pay * sin(-RS) + cub->coords.ply * cos(-RS);
	}
	if (cub->key[LEFT])
	{
		pax = cub->coords.pax;
		cub->coords.pax = cub->coords.pax * cos(RS) - cub->coords.pay * sin(RS);
		cub->coords.pay = pax * sin(RS) + cub->coords.pay * cos(RS);
		pay = cub->coords.plx;
		cub->coords.plx = cub->coords.plx * cos(RS) - cub->coords.ply * sin(RS);
		cub->coords.ply = pay * sin(RS) + cub->coords.ply * cos(RS);
	}
}

int			ft_key_hit(int keycode, t_cub *cub)
{
	if (keycode == K_W)
		cub->key[W] = 1;
	else if (keycode == K_S)
		cub->key[S] = 1;
	else if (keycode == K_LEFT)
		cub->key[LEFT] = 1;
	else if (keycode == K_RIGHT)
		cub->key[RIGHT] = 1;
	else if (keycode == K_A)
		cub->key[A] = 1;
	else if (keycode == K_D)
		cub->key[D] = 1;
	else if (keycode == K_ESC)
		cub->key[ESC] = 1;
	return (1);
}

int			ft_key_release(int keycode, t_cub *cub)
{
	if (keycode == K_W)
		cub->key[W] = 0;
	else if (keycode == K_S)
		cub->key[S] = 0;
	else if (keycode == K_LEFT)
		cub->key[LEFT] = 0;
	else if (keycode == K_RIGHT)
		cub->key[RIGHT] = 0;
	else if (keycode == K_A)
		cub->key[A] = 0;
	else if (keycode == K_D)
		cub->key[D] = 0;
	else if (keycode == K_ESC)
		cub->key[ESC] = 0;
	return (1);
}
