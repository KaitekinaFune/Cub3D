/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:41:29 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:48:57 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	check_sp_vert(t_cub *cub, int i, int j)
{
	int		y;
	int		x;

	y = i;
	x = j;
	while (cub->map[y][x])
	{
		y++;
		if (!cub->map[y] || cub->map[y][x] == '1')
			break ;
		if (cub->map[y][x] == '0')
			return (0);
	}
	y = i;
	x = j;
	while (y > 0)
	{
		y--;
		if (!cub->map[y] || cub->map[y][x] == '1')
			break ;
		if (cub->map[y][x] == '0')
			return (0);
	}
	return (1);
}

int
	check_sp_hori(t_cub *cub, int i, int j)
{
	int		y;
	int		x;

	y = i;
	x = j;
	while (x >= 0)
	{
		x--;
		if (!cub->map[y][x] || cub->map[y][x] == '1')
			break ;
		if (cub->map[y][x] == '0')
			return (0);
	}
	y = i;
	x = j;
	while (cub->map[y][x])
	{
		x++;
		if (!cub->map[y][x] || cub->map[y][x] == '1')
			break ;
		if (cub->map[y][x] == '0')
			return (0);
	}
	return (1);
}
