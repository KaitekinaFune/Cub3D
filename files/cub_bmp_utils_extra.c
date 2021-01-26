/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp_utils_extra.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:27:59 by lflint            #+#    #+#             */
/*   Updated: 2021/01/24 13:46:38 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	buf_ascii_map(unsigned int index, char c)
{
	(void)index;
	return (((unsigned char)c) & 0xFF);
}

t_buf	*buf_create(int length)
{
	t_buf *buf;

	if (!(buf = malloc(sizeof(t_buf))))
		return (NULL);
	buf->length = length;
	buf->data = ft_calloc(length, sizeof(char));
	if (buf->data == NULL)
	{
		free(buf);
		buf = NULL;
	}
	return (buf);
}

int		buf_poops(t_buf *buf, unsigned char *s, int offset, int len)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if (index + offset >= buf->length)
			break ;
		buf->data[index + offset] = s[index];
		index++;
	}
	return (index + offset);
}

void	buf_destroy(t_buf **buf_ptr)
{
	free((*buf_ptr)->data);
	(*buf_ptr)->length = 0;
	free(*buf_ptr);
	*buf_ptr = NULL;
}
