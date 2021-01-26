/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:25:29 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 14:44:08 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_txt_type(t_cub *cub)
{
	char	*temp;
	int		j;

	j = 0;
	while (j < 5)
	{
		temp = &cub->file.textures[j][cub->txt[j].i];
		if (check_ext(temp, ".png"))
			cub->file.toggle[j] = PNG;
		else if (check_ext(temp, ".xpm"))
			cub->file.toggle[j] = XPM;
		else
			file_error(cub, j + 1, NULL);
		j++;
	}
}

void		check_textures(t_cub *cub)
{
	int		i;
	int		fd;

	trim_texture(cub->txt, cub);
	i = 0;
	while (i < 5)
	{
		cub->file.toggle[i] = 0;
		fd = open(&cub->file.textures[i][cub->txt[i].i], O_RDONLY);
		if (fd < 0)
			file_error(cub, i + 1, NULL);
		close(fd);
		i++;
	}
	check_txt_type(cub);
}

int			is_color(char c)
{
	return ((c >= '0' && c <= '9') || c == ',' || c == ' ');
}

int			is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int			get_begin(char *str)
{
	int		i;

	i = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}
