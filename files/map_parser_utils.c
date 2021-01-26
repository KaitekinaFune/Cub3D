/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:38:14 by lflint            #+#    #+#             */
/*   Updated: 2021/01/19 12:31:20 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		resol_mode(char *line, t_cub *cub, int mode)
{
	if (!(parse_resol(line, cub)))
		file_error(cub, mode, line);
	free(line);
}

int			check_line(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] != '\0')
		return (1);
	else
	{
		free(line);
		return (0);
	}
}

void		skip_ws(char *line, int *j)
{
	while (line[*j] && (line[*j] == ' ' || line[*j] == '\t'))
		*j += 1;
}

int			check_ext(char *name, char *check)
{
	int		i;
	int		j;

	if (!name)
		return (-1);
	i = 0;
	while (name[i])
		i++;
	if (i <= 4)
		return (-1);
	else
		i -= 4;
	j = 0;
	while (name[i])
	{
		if (name[i] != check[j])
			return (0);
		j++;
		i++;
	}
	return (1);
}

int			ft_strchr(char *str, char c1, char c2)
{
	int		i;

	i = 0;
	if (str)
	{
		if (c2 != ' ')
		{
			if (str[0] == c1 && str[1] == c2 &&
			(str[2] == ' ' || str[2] == '\t'))
				return (1);
			i++;
		}
		else
		{
			if (str[i] == c1 && (str[1] == ' ' || str[1] == '\t'))
				return (1);
			i++;
		}
	}
	return (0);
}
