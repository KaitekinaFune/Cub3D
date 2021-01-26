/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 18:22:00 by lflint            #+#    #+#             */
/*   Updated: 2021/01/24 13:02:53 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		buf_ascii(t_buf *buf, char *s, int offset, int length)
{
	unsigned char	*bytes;
	int				new_pos;

	bytes = (unsigned char *)ft_strmapi(s, buf_ascii_map);
	if (!bytes)
		return ((int)-1);
	new_pos = buf_poops(buf, bytes, offset, length);
	free(bytes);
	return (new_pos);
}

int		bmp_encode_head(t_bmp_encode *encoder, t_buf *buf)
{
	int		pos;

	pos = 0;
	pos = buf_ascii(buf, encoder->head.flag, pos, 2);
	pos = buf_uint32(buf, encoder->head.file_size, pos);
	pos = buf_uint32(buf, encoder->head.reserved, pos);
	pos = buf_uint32(buf, encoder->head.offset, pos);
	pos = buf_uint32(buf, encoder->header_info_size, pos);
	pos = buf_uint32(buf, encoder->width, pos);
	pos = buf_int32(buf, -encoder->height, pos);
	pos = buf_uint16(buf, encoder->head.planes, pos);
	pos = buf_uint16(buf, encoder->head.bit_per_pixel, pos);
	pos = buf_uint32(buf, encoder->head.compress, pos);
	pos = buf_uint32(buf, encoder->rgb_size, pos);
	pos = buf_uint32(buf, encoder->head.hr, pos);
	pos = buf_uint32(buf, encoder->head.vr, pos);
	pos = buf_uint32(buf, encoder->head.colors, pos);
	pos = buf_uint32(buf, encoder->head.important_color, pos);
	return (pos);
}

int		cub_bmp(t_cub *cub)
{
	t_bmp_encode	encoder;
	t_buf			*buf;
	int				pos;
	int				fd;

	fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0664);
	bmp_init_encode(&encoder, cub);
	bmp_init_head(&encoder);
	buf = buf_create(encoder.head.offset + encoder.rgb_size);
	if (!buf)
	{
		write(1, "Error\nCouldn't write image\n", 27);
		cub_exit(cub, 14);
	}
	pos = bmp_encode_head(&encoder, buf);
	bmp_image_data(&encoder, buf, pos);
	write(fd, buf->data, buf->length);
	buf_destroy(&buf);
	close(fd);
	return (1);
}
