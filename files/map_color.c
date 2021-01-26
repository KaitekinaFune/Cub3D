/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:23:04 by lflint            #+#    #+#             */
/*   Updated: 2021/01/24 00:05:18 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_floor_color(t_cub *cub)
{
	cub->file.i = get_begin(cub->file.f_clr);
	while (cub->file.f_clr[cub->file.i])
	{
		if (is_digit(cub->file.f_clr[cub->file.i]) && cub->file.dot == 0)
			cub->file.f_r = cub->file.f_r * 10 + cub->file.f_clr[cub->file.i]
			- '0';
		else if (is_digit(cub->file.f_clr[cub->file.i]) && cub->file.dot == 1)
			cub->file.f_g = cub->file.f_g * 10 + cub->file.f_clr[cub->file.i]
			- '0';
		else if (is_digit(cub->file.f_clr[cub->file.i]) && cub->file.dot == 2)
		{
			cub->file.count++;
			cub->file.f_b = cub->file.f_b * 10 + cub->file.f_clr[cub->file.i]
			- '0';
		}
		else if (cub->file.f_clr[cub->file.i] == ',')
			cub->file.dot++;
		else
			file_error(cub, 6, NULL);
		cub->file.i++;
		cub->file.chars++;
	}
	if (cub->file.dot != 2 || cub->file.count == 0 || cub->file.f_r > 255
	|| cub->file.f_g > 255 || cub->file.f_b > 255 || cub->file.chars > 11)
		file_error(cub, 6, NULL);
}

static void	assign_ceiling_color(t_cub *cub)
{
	cub->file.i = get_begin(cub->file.c_clr);
	while (cub->file.c_clr[cub->file.i])
	{
		if (is_digit(cub->file.c_clr[cub->file.i]) && cub->file.dot == 0)
			cub->file.c_r = cub->file.c_r * 10 + cub->file.c_clr[cub->file.i]
			- '0';
		else if (is_digit(cub->file.c_clr[cub->file.i]) && cub->file.dot == 1)
			cub->file.c_g = cub->file.c_g * 10 + cub->file.c_clr[cub->file.i]
			- '0';
		else if (is_digit(cub->file.c_clr[cub->file.i]) && cub->file.dot == 2)
		{
			cub->file.count++;
			cub->file.c_b = cub->file.c_b * 10 + cub->file.c_clr[cub->file.i]
			- '0';
		}
		else if (cub->file.c_clr[cub->file.i] == ',')
			cub->file.dot++;
		else
			file_error(cub, 7, NULL);
		cub->file.chars++;
		cub->file.i++;
	}
	if (cub->file.dot != 2 || cub->file.count == 0 || cub->file.c_r > 255
	|| cub->file.c_g > 255 || cub->file.c_b > 255 || cub->file.chars > 11)
		file_error(cub, 7, NULL);
}

static void	get_hex_color(t_cub *cub)
{
	cub->file.f_rgb = cub->file.f_r;
	cub->file.f_rgb = (cub->file.f_rgb << 8) + cub->file.f_g;
	cub->file.f_rgb = (cub->file.f_rgb << 8) + cub->file.f_b;
	cub->file.c_rgb = cub->file.c_r;
	cub->file.c_rgb = (cub->file.c_rgb << 8) + cub->file.c_g;
	cub->file.c_rgb = (cub->file.c_rgb << 8) + cub->file.c_b;
}

static void	assign_colors(t_cub *cub)
{
	cub->file.count = 0;
	cub->file.i = 0;
	cub->file.f_r = 0;
	cub->file.f_g = 0;
	cub->file.f_b = 0;
	cub->file.f_rgb = 0;
	cub->file.dot = 0;
	cub->file.chars = 0;
	assign_floor_color(cub);
	cub->file.count = 0;
	cub->file.i = 0;
	cub->file.c_r = 0;
	cub->file.c_g = 0;
	cub->file.c_b = 0;
	cub->file.c_rgb = 0;
	cub->file.dot = 0;
	cub->file.chars = 0;
	assign_ceiling_color(cub);
	get_hex_color(cub);
}

void		check_colors(t_cub *cub)
{
	int		i;

	i = 1;
	while (cub->file.c_clr[i])
	{
		if (!is_color(cub->file.c_clr[i]))
			file_error(cub, 7, NULL);
		i++;
	}
	i = 1;
	while (cub->file.f_clr[i])
	{
		if (!is_color(cub->file.f_clr[i]))
			file_error(cub, 6, NULL);
		i++;
	}
	assign_colors(cub);
}
