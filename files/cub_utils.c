/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:31:25 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 23:42:17 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_strdup(const char *s1)
{
	size_t	len;
	void	*s2;

	len = ft_strlen(s1) + 1;
	if ((s2 = malloc(len)) == NULL)
		return (NULL);
	return ((char*)ft_memcpy(s2, s1, len));
}

size_t		ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int			empty_line(char *line)
{
	int		i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

int			ft_core(t_cub *cub)
{
	if (cub->key[W] || cub->key[S])
		key_vert(cub);
	if (cub->key[LEFT] || cub->key[RIGHT])
		key_hori(cub);
	if (cub->key[A] || cub->key[D])
		key_side(cub);
	if (cub->key[ESC])
		cub_exit(cub, 0);
	if (cub->key[W] || cub->key[S] || cub->key[LEFT] || cub->key[RIGHT]
	|| cub->key[A] || cub->key[D])
	{
		image_destroy(&cub->mlx);
		count_rays(cub, cub->txt);
		mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.img, 0, 0);
	}
	return (1);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char *d;
	char *s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}
