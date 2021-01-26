/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp_encoder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:29:27 by lflint            #+#    #+#             */
/*   Updated: 2021/01/24 13:18:05 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			buf_int32(t_buf *buf, int value, int offset)
{
	value = +value;
	offset = bmp_bitshift(offset, 0);
	buf->data[offset + 0] = value & 0xFF;
	buf->data[offset + 1] = bmp_bitshift(value, 8) & 0xFF;
	buf->data[offset + 2] = bmp_bitshift(value, 16) & 0xFF;
	buf->data[offset + 3] = bmp_bitshift(value, 24) & 0xFF;
	return (offset + 4);
}

int			buf_uint16(t_buf *buf, unsigned int value, int offset)
{
	value = +value;
	offset = bmp_bitshift(offset, 0);
	buf->data[offset + 0] = value & 0xFF;
	buf->data[offset + 1] = bmp_bitshift(value, 8) & 0xFF;
	return (offset + 2);
}

int			buf_uint32(t_buf *buf, unsigned int value, int offset)
{
	value = +value;
	offset = bmp_bitshift(offset, 0);
	buf->data[offset + 3] = bmp_bitshift(value, 24) & 0xFF;
	buf->data[offset + 2] = bmp_bitshift(value, 16) & 0xFF;
	buf->data[offset + 1] = bmp_bitshift(value, 8) & 0xFF;
	buf->data[offset + 0] = value & 0xFF;
	return (offset + 4);
}

static void	bmp_image_data_extra(t_bmp_encode *encoder, t_buf *buf,
int pos, int y)
{
	int offset;

	offset = pos + y * encoder->row_bytes + encoder->width * 3;
	buf_fill(buf, 0, offset, offset + encoder->extra_bytes);
}

void		bmp_image_data(t_bmp_encode *encoder, t_buf *buf, int pos)
{
	int		index;
	int		offset;
	int		buf_offset;
	t_vec	vec;

	vec = (t_vec) { 0, 0, };
	index = 0;
	while (vec.y < encoder->height)
	{
		vec.x = 0;
		while (vec.x < encoder->width)
		{
			offset = pos + vec.y * encoder->row_bytes + vec.x * 3;
			buf_offset = encoder->buf_bytes * vec.y + vec.x * 4;
			buf->data[offset + 0] = encoder->buf[buf_offset + 0];
			buf->data[offset + 1] = encoder->buf[buf_offset + 1];
			buf->data[offset + 2] = encoder->buf[buf_offset + 2];
			index += 4;
			vec.x += 1;
		}
		if (encoder->extra_bytes > 0)
			bmp_image_data_extra(encoder, buf, pos, vec.y);
		vec.y += 1;
	}
}
