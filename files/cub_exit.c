/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:34:05 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 15:50:37 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_map(t_cub *cub)
{
	int		i;

	i = -1;
	while (cub->map[++i])
		free(cub->map[i]);
	free(cub->map);
}

int			catch_cross(t_cub *cub)
{
	cub_exit(cub, 0);
	return (1);
}

void		cub_exit(t_cub *cub, int i)
{
	int		j;

	j = -1;
	while (cub->txt[++j].img)
	{
		if (cub->txt[j].img)
			mlx_destroy_image(cub->mlx.mlx, cub->txt[j].img);
		cub->txt[j].img = NULL;
	}
	if (cub->sprites)
		free(cub->sprites);
	image_destroy(&cub->mlx);
	free_map(cub);
	if (i != 2)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	free(cub->mlx.mlx);
	exit(0);
}
