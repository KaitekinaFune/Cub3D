/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bmp_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 12:18:57 by lflint            #+#    #+#             */
/*   Updated: 2021/01/24 13:46:19 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	bmp_init_encode(t_bmp_encode *encoder, t_cub *cub)
{
	encoder->buf = (char *)cub->mlx.addr;
	encoder->width = cub->mlx.scr_w;
	encoder->height = cub->mlx.scr_h;
	encoder->extra_bytes = encoder->width % 4;
	encoder->rgb_size = encoder->height *
							(3 * encoder->width + encoder->extra_bytes);
	encoder->header_info_size = 40;
	encoder->row_bytes = 3 * encoder->width + encoder->extra_bytes;
	encoder->buf_bytes = cub->mlx.lin_l;
}

void	bmp_init_head(t_bmp_encode *encoder)
{
	t_bmp_head	*head;

	head = &(encoder->head);
	head->flag = "BM";
	head->reserved = 0;
	head->offset = 54;
	head->file_size = encoder->rgb_size + head->offset;
	head->planes = 1;
	head->bit_per_pixel = 24;
	head->compress = 0;
	head->hr = 0;
	head->vr = 0;
	head->colors = 0;
	head->important_color = 0;
}

int		bmp_bitshift(int x, int n)
{
	return (int)((unsigned int)x >> n);
}

void	buf_fill(t_buf *buf, unsigned char value, int start, int end)
{
	int	index;

	index = start;
	while (index < end && index < buf->length)
	{
		buf->data[index] = value;
		index++;
	}
}
