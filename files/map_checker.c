/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:32:50 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 17:01:50 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	check_zero_vert(t_cub *cub, int i, int j)
{
	int		y;
	int		x;

	y = i;
	x = j;
	while (cub->map[y][x])
	{
		if (!cub->map[y + 1] || cub->map[y + 1][x] == '\0' || cub->map[y][x]
		== ' ')
			return (0);
		y++;
		if (cub->map[y][x] == '1')
			break ;
	}
	y = i;
	x = j;
	while (y >= 0)
	{
		if (!cub->map[y - 1][x] || y == 0 || cub->map[y - 1][x] == ' ')
			return (0);
		y--;
		if (cub->map[y][x] == '1')
			break ;
	}
	return (i == 0 ? 0 : 1);
}

static int
	check_zero_hori(t_cub *cub, int i, int j)
{
	int		y;
	int		x;

	y = i;
	x = j;
	while (x >= 0)
	{
		if (x == 0 || cub->map[y][x] == ' ')
			return (0);
		x--;
		if (cub->map[y][x] == '1')
			break ;
	}
	y = i;
	x = j;
	while (cub->map[y][x])
	{
		if (!cub->map[y][x + 1] || cub->map[y][x + 1] == ' ')
			return (0);
		x++;
		if (cub->map[y][x] == '1')
			break ;
	}
	return (1);
}

int
	map_holes(t_cub *cub)
{
	int		x;
	int		y;

	y = 0;
	while (cub->map[y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '0')
			{
				if (!check_zero_vert(cub, y, x) || !check_zero_hori(cub, y, x))
					return (0);
			}
		}
		y++;
	}
	return (1);
}

int
	map_content(t_cub *cub)
{
	int		x;
	int		y;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (!is_map(cub->map[y][x]) && cub->map[y][x] != ' ')
				cub_error(15, cub, "Bad map\n");
			else if (cub->map[y][x] == ' ')
			{
				if (!check_sp_vert(cub, y, x) || !check_sp_hori(cub, y, x))
					cub_error(15, cub, "Hole in Map\n");
			}
			x++;
		}
		y++;
	}
	return (1);
}
