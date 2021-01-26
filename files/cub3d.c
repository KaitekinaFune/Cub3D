/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:39 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 15:07:13 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_struct(t_cub *cub)
{
	int		i;

	i = -1;
	cub->force = 0;
	cub->mlx.scr_w = 0;
	cub->mlx.scr_h = 0;
	while (++i < KEYSIZE)
		cub->key[i] = 0;
}

void		map_parser(char *map_name, int mode)
{
	t_cub	*cub;

	if (!(cub = malloc(sizeof(*cub))))
		cub_error(15, cub, "No memory\n");
	init_struct(cub);
	get_file(cub, map_name);
	if (!(get_map(cub, map_name)))
		cub_error(8, cub, "Bad map\n");
	if (!(map_holes(cub)))
		cub_error(9, cub, "Hole in map\n");
	check_textures(cub);
	check_colors(cub);
	cub_init(cub, mode);
}

void		check_save_arg(char *str, char *format)
{
	int		i;

	if (!str)
		cub_error(0, NULL, "Invalid arguments\n");
	i = 0;
	while (str[i])
	{
		if (str[i] != format[i])
			cub_error(0, NULL, "Invalid arguments\n");
		i++;
	}
	if (i != 6)
		cub_error(0, NULL, "Invalid arguments\n");
}

int			main(int argc, char **argv)
{
	if (argc == 1)
		cub_error(0, NULL, "No File\n");
	else if (argc == 2)
		map_parser(argv[1], 0);
	else if (argc == 3)
	{
		check_save_arg(argv[2], "--save");
		map_parser(argv[1], 1);
	}
	else
		cub_error(0, NULL, "Invalid arguments\n");
}
