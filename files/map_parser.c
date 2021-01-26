/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:39:05 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:51:24 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	parse_resol(char *line, t_cub *cub)
{
	int		i;

	i = 2;
	skip_ws(line, &i);
	while (line[i])
	{
		if (line[i] >= '0' && line[i] <= '9' && !cub->file.space)
			cub->mlx.scr_w = cub->mlx.scr_w * 10 + line[i] - '0';
		else if (line[i] == ' ' || line[i] == '\t')
		{
			if (cub->mlx.scr_w > 0 && !cub->file.space)
				cub->file.space = 1;
			skip_ws(line, &i);
			i--;
		}
		else if (line[i] >= '0' && line[i] <= '9' && cub->file.space)
			cub->mlx.scr_h = cub->mlx.scr_h * 10 + line[i] - '0';
		else
			return (0);
		i++;
	}
	cub->mlx.scr_w = (cub->mlx.scr_w > MAXRESW ? MAXRESW : cub->mlx.scr_w);
	cub->mlx.scr_h = (cub->mlx.scr_h > MAXRESH ? MAXRESH : cub->mlx.scr_h);
	return (cub->mlx.scr_w <= 0 || cub->mlx.scr_h <= 0 ? 0 : 1);
}

static int
	check_texture(t_cub *cub, char *line, int mode)
{
	int		i;

	i = 0;
	if (mode > 0 && mode < 5)
		i = 2;
	else
		i = 1;
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	if (!line[i])
		file_error(cub, mode, line);
	return (i);
}

static void
	parse_texture(char *line, t_cub *cub, int mode)
{
	int		i;

	i = check_texture(cub, line, mode);
	if (mode >= 1 && mode <= 5)
		cub->file.textures[mode - 1] = ft_strdup(&line[i]);
	else if (mode == 6)
		cub->file.colors[0] = ft_strdup(&line[i]);
	else if (mode == 7)
		cub->file.colors[1] = ft_strdup(&line[i]);
	free(line);
}

static int
	get_args(char *line, t_cub *cub, int mode)
{
	if (ft_strchr(line, 'R', ' ') && mode == 0)
		resol_mode(line, cub, mode);
	else if (ft_strchr(line, 'N', 'O') && mode == 1)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'S', 'O') && mode == 2)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'W', 'E') && mode == 3)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'E', 'A') && mode == 4)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'S', ' ') && mode == 5)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'F', ' ') && mode == 6)
		parse_texture(line, cub, mode);
	else if (ft_strchr(line, 'C', ' ') && mode == 7)
		parse_texture(line, cub, mode);
	else
		return (0);
	return (1);
}

void
	get_file(t_cub *cub, char *map_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	cub->file.space = 0;
	if (!(check_ext(map_name, ".cub")))
		cub_error(4, cub, "Invalid File Extension\n");
	if ((fd = open(map_name, O_RDONLY)) < 0)
		cub_error(5, cub, "Bad Map File\n");
	while (get_next_line(fd, &line) && i <= 7)
	{
		if (check_line(line))
		{
			if (!get_args(line, cub, i++))
				file_error(cub, i - 1, line);
		}
	}
	close(fd);
	if (line)
		free(line);
	if (i == 0)
		cub_error(3, cub, "Empty file?\n");
}
