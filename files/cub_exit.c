/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:34:05 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 14:42:58 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			free_map(t_cub *cub)
{
	int		i;

	i = 0;
	while (cub->data[i] != NULL)
	{
		free(cub->data[i]);
		i++;
	}
	free(cub->data);
}

void			cub_error(int err_num, t_cub *cub, char *err)
{
	write(1, "Error\n", 6);
	write(1, err, ft_strlen(err));
	if (err_num > 2)
		free_file(cub, NULL);
	if (err_num > 4)
		free_map(cub);
	exit(err_num);
}

void			free_file(t_cub *cub, char *line)
{
	int		i;

	i = -1;
	while (cub->file.textures[++i] && i < 5)
		free(cub->file.textures[i]);
	if (cub->file.f_clr)
		free(cub->file.f_clr);
	if (cub->file.c_clr)
		free(cub->file.c_clr);
	if (cub)
		free(cub);
	if (line)
		free(line);
}

void			file_error(t_cub *cub, int mode, char *line)
{
	write(1, "Error\n", 6);
	if (mode == 0)
		write(1, "Invalid resolution\n", 19);
	else if (mode == 1)
		write(1, "Invalid north texture\n", 22);
	else if (mode == 2)
		write(1, "Invalid south texture\n", 22);
	else if (mode == 3)
		write(1, "Invalid west texture\n", 21);
	else if (mode == 4)
		write(1, "Invalid east texture\n", 21);
	else if (mode == 5)
		write(1, "Invalid sprite texture\n", 23);
	else if (mode == 6)
		write(1, "Invalid floor color\n", 20);
	else if (mode == 7)
		write(1, "Invalid ceiling color\n", 22);
	else if (mode == 8)
		write(1, "Unknown error\n", 14);
	else if (mode == 9)
		write(1, "Empty or small map\n", 19);
	free_file(cub, line);
	exit(1);
}

void			cub_exit(t_cub *cub, int i)
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
	free_file(cub, NULL);
	if (i != 2)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.win);
	free(cub->mlx.mlx);
	if (i == 13)
	{
		write(1, "Error\nInvalid texture file\n", 27);
		exit(i);
	}
	exit(0);
}
