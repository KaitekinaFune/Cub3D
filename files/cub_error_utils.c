/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflint <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:44:49 by lflint            #+#    #+#             */
/*   Updated: 2021/01/25 19:46:07 by lflint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			free_textures(t_cub *cub, int err)
{
	int		i;

	i = err - 6;
	while (i >= 0)
		free(cub->file.textures[i--]);
}

void			free_textures_extra(t_cub *cub, int err)
{
	int		i;

	i = err - 18;
	while (i <= 22)
		free(cub->file.textures[i++]);
}

void			free_colors(t_cub *cub, int err)
{
	int		i;

	i = err - 11;
	while (i >= 0)
		free(cub->file.colors[i--]);
}
