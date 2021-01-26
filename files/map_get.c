/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:33:32 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:36:02 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			free_temp(char *str)
{
	free(str);
	return (0);
}

static int			map_size(char *map_name)
{
	t_t_buf buf;
	buf.i = 0;
	buf.toggle = 0;
	buf.fd = open(map_name, O_RDONLY);
	while (get_next_line(buf.fd, &buf.temp))
	{
		if (buf.toggle == 0 && ft_strchr(buf.temp, 'C', ' '))
			buf.toggle = 1;
		else if (buf.toggle == 1 && !empty_line(buf.temp))
			buf.toggle = 2;
		else if (buf.toggle == 2 && empty_line(buf.temp))
			buf.toggle = 3;
		else if (buf.toggle == 3 && !empty_line(buf.temp))
			return (free_temp(buf.temp));
		if (buf.toggle == 2)
			buf.i += 1;
		free(buf.temp);
	}
	if (buf.toggle == 3 && !empty_line(buf.temp))
		return (free_temp(buf.temp));
	free(buf.temp);
	close(buf.fd);
	return (buf.i <= 2 ? 0 : buf.i);
}

static void		get_to_map(t_cub *cub, int fd)
{
	char	*temp;
	
	while (get_next_line(fd, &temp))
	{
		if (ft_strchr(temp, 'C', ' '))
			break ;
		free(temp);
	}
	free(temp);
	while (get_next_line(fd, &temp))
	{
		if (!empty_line(temp))
		{
			cub->map[0] = ft_strdup(temp);
			free(temp);
			break;
		}
		free(temp);
	}
}

int			get_map(t_cub *cub, char *map_name)
{
	int		i;
	int		j;
	int		fd;
	
	if (!(i = map_size(map_name)))
		cub_error(14, cub, "Bad Map!\n");
	if (!(cub->map = malloc(sizeof(char *) * i)))
	{
		free(cub);
		exit(-1);
	} 
	fd = open(map_name, O_RDONLY);
	get_to_map(cub, fd);
	j = 1;
	while (get_next_line(fd, &cub->map[j]) && j < i)
		j++;
	if (empty_line(cub->map[j]))
	{
		free(cub->map[j]);
		cub->map[j] = NULL;
	}	
	else
		cub->map[j + 1] = NULL;
	map_content(cub);
	return (1);
}
