/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:39 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:20:03 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_struct(t_cub *cub)
{
	int		i;

	i = -1;
	cub->mlx.scr_w = 0;
	cub->mlx.scr_h = 0;
	while (++i < KEYSIZE)
		cub->key[i] = 0;
}

static void	map_parser(char *map_name, int mode)
{
	t_cub	*cub;

	if (!(cub = malloc(sizeof(t_cub))))
		cub_error(3, cub, "No memory\n");
	init_struct(cub);
	get_file(cub, map_name);
	check_textures(cub);
	check_colors(cub);
	get_map(cub, map_name);
	if (!(map_holes(cub)))
		cub_error(14, cub, "Hole in map\n");
	cub_init(cub, mode);
}

static int	check_save_arg(char *str, char *format)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != format[i])
			return (0);
		i++;
	}
	if (i != 6)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	if (argc == 1)
		cub_error(1, NULL, "No File\n");
	else if (argc == 2)
		map_parser(argv[1], 0);
	else if (argc == 3)
	{
		if (!(check_save_arg(argv[2], "--save")))
			cub_error(2, NULL, "Invalid arguments\n");
		map_parser(argv[1], 1);
	}
	else
		cub_error(2, NULL, "Invalid arguments\n");
}
