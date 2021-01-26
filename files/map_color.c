/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:23:04 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:49:11 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	assign_color(char *color, t_cub *cub, t_rgb *type)
{
	while (color[cub->file.i])
	{
		if (is_digit(color[cub->file.i]) && cub->file.dot == 0)
			type->r = type->r * 10 + color[cub->file.i]
			- '0';
		else if (is_digit(color[cub->file.i]) && cub->file.dot == 1)
			type->g = type->g * 10 + color[cub->file.i]
			- '0';
		else if (is_digit(color[cub->file.i]) && cub->file.dot == 2)
		{
			cub->file.count++;
			type->b = type->b * 10 + color[cub->file.i]
			- '0';
		}
		else if (color[cub->file.i] == ',')
			cub->file.dot++;
		cub->file.chars++;
		cub->file.i++;
	}
	if (cub->file.dot != 2 || cub->file.count == 0 || type->r > 255
	|| type->g > 255 || type->b > 255 || cub->file.chars > 11)
		return (0);
	return (1);
}

static int	get_hex_rgb(t_rgb type)
{
	int		rgb;

	rgb = type.r;
	rgb = (rgb << 8) + type.g;
	rgb = (rgb << 8) + type.b;
	return (rgb);
}

static void	refresh_counter(t_cub *cub)
{
	cub->file.count = 0;
	cub->file.dot = 0;
	cub->file.i = 0;
	cub->file.chars = 0;
}

static void	assign_colors(t_cub *cub)
{
	t_rgb	f;
	t_rgb	c;

	f = (t_rgb) { 0, 0, 0, };
	c = (t_rgb) { 0, 0, 0, };
	refresh_counter(cub);
	if (!(assign_color(cub->file.colors[0], cub, &f)))
		cub_error(13, cub, "Invalid RGB color\n");
	refresh_counter(cub);
	if (!(assign_color(cub->file.colors[1], cub, &c)))
		cub_error(13, cub, "Invalid RGB color\n");
	cub->file.f_rgb = get_hex_rgb(f);
	cub->file.c_rgb = get_hex_rgb(c);
}

void		check_colors(t_cub *cub)
{
	int		i;
	int		type;

	type = 0;
	while (type < 2)
	{
		i = 0;
		while (cub->file.colors[type][i])
		{
			if (!is_color(cub->file.colors[type][i]))
				cub_error(17, cub, "Invalid RGB color\n");
			i++;
		}
		type++;
	}
	assign_colors(cub);
	free(cub->file.colors[0]);
	free(cub->file.colors[1]);
}
