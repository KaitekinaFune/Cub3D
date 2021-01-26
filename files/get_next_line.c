/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:14:27 by lflint            #+#    #+#             */
/*   Updated: 2021/01/19 15:19:57 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int			gnl_parse(t_gnl *gnl, int force, int return_value)
{
	if (!(gnl->done == 1 && !force))
	{
		gnl->done = 1;
		gnl->reach = 0;
		gnl->buf_size = BUFFER_SIZE;
		gnl->line = NULL;
		gnl->lin_l = 0;
	}
	return (return_value);
}

static char			*gnl_store(t_gnl *gnl, int force)
{
	char	c;
	char	*str;

	c = gnl->buf[gnl->buf_size];
	gnl->buf_size += 1;
	if (!(str = malloc((gnl->lin_l + 1) * sizeof(char))))
		return (NULL);
	if (gnl->line != NULL)
	{
		ft_memcpy(str, gnl->line, gnl->lin_l);
		free(gnl->line);
	}
	if (c == '\n' || force)
	{
		str[gnl->lin_l] = '\0';
		gnl->line = NULL;
		gnl->lin_l = 0;
		return (str);
	}
	str[gnl->lin_l] = c;
	gnl->lin_l += 1;
	gnl->line = str;
	return (NULL);
}

static int			gnl_read(t_gnl *gnl, char **ret_line)
{
	char	*str;
	int		force;

	while (gnl->buf_size < BUFFER_SIZE)
	{
		force = gnl->buf_size >= gnl->bytes;
		str = gnl_store(gnl, force);
		if (str != NULL)
		{
			if (force)
				gnl->reach = 1;
			*ret_line = (char *)str;
			return (1);
		}
	}
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static t_gnl		gnl;

	if (line == NULL || BUFFER_SIZE == 0 || fd < 0)
		return (-1);
	gnl_parse(&gnl, 0, 1);
	while (42 > 21)
	{
		if (gnl.buf_size == BUFFER_SIZE)
		{
			gnl.bytes = read(fd, gnl.buf, BUFFER_SIZE);
			gnl.buf_size = 0;
		}
		if (gnl.bytes == (size_t)-1)
			return (-1);
		if (gnl_read(&gnl, line))
		{
			if (gnl.bytes == 0 || gnl.reach)
				return (gnl_parse(&gnl, 1, 0));
			return (1);
		}
	}
}
