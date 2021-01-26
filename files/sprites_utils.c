/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:31:16 by lflint            #+#    #+#             */
/*   Updated: 2021/01/23 19:21:34 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sort_sprites(t_cub *cub)
{
	int			i;
	int			j;
	t_sprite	key;

	i = 1;
	while (i < cub->sprite_count)
	{
		key = cub->sprites[i];
		j = i - 1;
		while (j >= 0 && cub->sprites[j].dist < key.dist)
		{
			cub->sprites[j + 1] = cub->sprites[j];
			j = j - 1;
		}
		cub->sprites[j + 1] = key;
		i++;
	}
}

int			count_sprites(t_cub *cub)
{
	int		i;
	int		j;

	cub->sprite_count = 0;
	i = 0;
	while (cub->map[i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '2')
				cub->sprite_count += 1;
		}
		i++;
	}
	return (cub->sprite_count);
}

void		count_sort_sprites(t_cub *cub)
{
	int		i;

	i = 0;
	while (i < cub->sprite_count)
	{
		cub->sprites[i].dist = ((cub->coords.px - cub->sprites[i].x) *
		(cub->coords.px - cub->sprites[i].x) + (cub->coords.py
		- cub->sprites[i].y) * (cub->coords.py - cub->sprites[i].y));
		i++;
	}
	sort_sprites(cub);
}

void		get_sprites(t_cub *cub)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	if (!(cub->sprites = malloc(cub->sprite_count * sizeof(t_sprite))))
		cub_error(14, cub, "Insufficient memory\n");
	i = 0;
	while (cub->map[i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == '2')
			{
				cub->sprites[count].x = j;
				cub->sprites[count].y = i;
				count++;
			}
		}
		i++;
	}
}
