/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:33:32 by lflint            #+#    #+#             */
/*   Updated: 2021/01/26 15:13:18 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			clean_map(t_cub *cub)
{
	int		i;

	i = 0;
	if (!(skip_args(cub)))
		return (0);
	if (!(before_map(cub)))
		return (0);
	if (!(during_map(cub, &i)))
		return (0);
	if (!cub->force)
		if (!(after_map(cub, &i)))
			return (0);
	if (!cub->map[i])
		return (1);
	if (!cub->map[i][0])
	{
		free(cub->map[i]);
		cub->map[i] = NULL;
	}
	return (1);
}

int			check_another_time(int fd, char *temp, int i, t_cub *cub)
{
	int		ret;
	int		toggle;
	
	if (ft_strchr(temp, 'C', ' '))
	{
		free(temp);
		toggle = 1;
	}
	i = 0;
	while ((ret = (get_next_line(fd, &temp))) >= 0)
	{
		if (ft_strchr(temp, 'C', ' '))
			toggle = 1;
		i++;
		if (toggle != 0)
			toggle++;
		if (ret == 0)
			break ;
		free(temp);	
	}
	cub->force = 1;
	return (toggle <= 1 ? 0 : i);
}

int			map_size(char *map_name, t_cub *cub)
{
	char	*temp;
	int		i;
	int		fd;
	int		toggle;

	temp = NULL;
	toggle = 0;
	i = 0;
	fd = open(map_name, O_RDONLY);
	while (get_next_line(fd, &temp))
	{
		if (ft_strchr(temp, 'C', ' '))
			toggle = 1;
		i++;
		if (toggle != 0)
			toggle++;
		free(temp);	
	}
	if (get_next_line(fd, &temp) != 0)
		return (check_another_time(fd, temp, i, cub));
	close(fd);
	if (temp)
		free(temp);
	return (toggle <= 1 ? 0 : i);
}

int			get_map(t_cub *cub, char *map_name)
{
	int		i;
	int		fd;

	cub->map = NULL;
	i = map_size(map_name, cub);
	if (i <= 2)
		file_error(cub, 9, NULL);
	if (!(cub->data = malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	fd = open(map_name, O_RDONLY);
	while (get_next_line(fd, &cub->data[i]))
		i++;
	cub->map = cub->data;
	if (!(clean_map(cub)))
		return (0);
	return (map_content(cub));
}
