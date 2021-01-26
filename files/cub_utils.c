/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:25 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 14:45:42 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int			empty_line(char *line)
{
	int		i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int			catch_cross(t_cub *cub)
{
	cub_exit(cub, 0);
	return (1);
}

int			ft_core(t_cub *cub)
{
	if (cub->key[W] || cub->key[S])
		key_vert(cub);
	if (cub->key[LEFT] || cub->key[RIGHT])
		key_hori(cub);
	if (cub->key[A] || cub->key[D])
		key_side(cub);
	if (cub->key[ESC])
		cub_exit(cub, 0);
	if (cub->key[W] || cub->key[S] || cub->key[LEFT] || cub->key[RIGHT]
	|| cub->key[A] || cub->key[D])
	{
		image_destroy(&cub->mlx);
		count_rays(cub, cub->txt);
		mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	}
	return (1);
}
