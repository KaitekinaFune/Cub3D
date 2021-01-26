/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:43 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 13:45:00 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			is_map(char c)
{
	return ((c >= '0' && c <= '2') || c == 'N' || c == 'S' ||
			c == 'W' || c == 'E');
}

int			before_map(t_cub *cub)
{
	int		i;
	char	*temp;

	i = 0;
	while (cub->map[i])
	{
		temp = cub->map[i];
		if (!empty_line(temp))
		{
			cub->map = &cub->map[i];
			return (1);
		}
		else
			cub->map = &cub->map[i + 1];
	}
	return (0);
}

int			during_map(t_cub *cub, int *i)
{
	char	*temp;

	while (cub->map[*i])
	{
		if (!cub->map[*i + 1])
			return (1);
		temp = cub->map[*i];
		if (empty_line(temp))
			return (1);
		else
			*i += 1;
	}
	return (0);
}

int			after_map(t_cub *cub, int *i)
{
	if (!cub->map[*i + 1])
	{
		cub->map[*i + 1] = NULL;
		return (1);
	}
	else
		return (0);
}