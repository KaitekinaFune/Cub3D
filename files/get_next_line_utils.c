/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:34:55 by lflint            #+#    #+#             */
/*   Updated: 2021/01/12 20:48:19 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (dst == NULL && src == NULL)
		return (dst);
	while (n--)
		((unsigned char *)dst)[n] = ((unsigned char *)src)[n];
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	char *ptr;

	ptr = s;
	while (n--)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void *s;

	if ((s = malloc(count * size)) == NULL)
		return (NULL);
	if (s)
		ft_bzero(s, count * size);
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	char	*str;
	int		i;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		if (!(str = (char*)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1))))
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = s2[i];
		return (str);
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 == *s2++ && (--n))
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}
