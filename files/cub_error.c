/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:45:00 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 16:09:46 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		cub_error_extra(int err_num, t_cub *cub)
{
	if (err_num == 14)
		free_textures(cub, 10);
	else if (err_num < 18)
	{
		free_textures(cub, 10);
		free_map(cub);
	}
	else if (err_num >= 18 && err_num <= 22)
	{
		free_textures_extra(cub, err_num);
		free_map(cub);
	}
	else if (err_num > 22)
	{
		free_textures(cub, 10);
		free_map(cub);
	}
	exit(err_num);
}

void			cub_error(int err_num, t_cub *cub, char *err)
{
	write(1, "Error\n", 6);
	write(1, err, ft_strlen(err));
	if (err_num >= 3 && err_num <= 5)
		exit(err_num);
	else if (err_num >= 7 && err_num <= 10)
		free_textures(cub, err_num);
	else if (err_num == 11 || err_num == 12)
	{
		free_textures(cub, 10);
		free_colors(cub, err_num);
	}
	else if (err_num == 13)
	{
		free_textures(cub, 10);
		free_colors(cub, 12);
	}
	else if (err_num > 13)
		cub_error_extra(err_num, cub);
	exit(err_num);
}

void			file_error(t_cub *cub, int mode, char *line)
{
	if (line)
		free(line);
	if (mode == 0)
		cub_error(mode + 6, cub, "Invalid resolution\n");
	else if (mode == 1)
		cub_error(mode + 6, cub, "Invalid north texture\n");
	else if (mode == 2)
		cub_error(mode + 6, cub, "Invalid south texture\n");
	else if (mode == 3)
		cub_error(mode + 6, cub, "Invalid west texture\n");
	else if (mode == 4)
		cub_error(mode + 6, cub, "Invalid east texture\n");
	else if (mode == 5)
		cub_error(mode + 6, cub, "Invalid sprite texture\n");
	else if (mode == 6)
		cub_error(mode + 6, cub, "Invalid floor color\n");
	else if (mode == 7)
		cub_error(mode + 6, cub, "Invalid ceiling color\n");
	else if (mode == 8)
		cub_error(mode + 6, cub, "Unknown error\n");
}
