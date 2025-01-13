/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:46:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/13 18:24:06 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include <fcntl.h>

static char	**get_sprite_name_ptr(t_cub *cub, t_pars_data *d)
{
	int			i;

	if (!ft_strncmp(d->line, "S_", 2) && d->line[2])
	{
		if (d->line[2] >= 'a' && d->line[2] <= 'z' && (d->line[3] == ' '
			|| d->line[3] == '\n'))
		{
			i = 0;
			while (d->names[i])
			{
				if (d->names[i] == d->line[2])
					return (NULL);
				i++;
			}
			if (i == 26)
				return (NULL);
			d->sprites[i].name = d->line[2];
			d->names[i] = d->line[2];
			return (&d->sprites[i].tex.name);
		}
	}
	return (NULL);
}

static char	**get_name_ptr(t_cub *cub, t_pars_data *d)
{
	if (!ft_strncmp(d->line, "NO ", 3))
		return (&cub->map.nor_tex.name);
	if (!ft_strncmp(d->line, "SO ", 3))
		return (&cub->map.sou_tex.name);
	if (!ft_strncmp(d->line, "WE ", 3))
		return (&cub->map.wes_tex.name);
	if (!ft_strncmp(d->line, "EA ", 3))
		return (&cub->map.eas_tex.name);
	if (!ft_strncmp(d->line, "C ", 2))
		return (&cub->map.ceil_tex.name);
	if (!ft_strncmp(d->line, "F ", 2))
		return (&cub->map.floor_tex.name);
	if (!ft_strncmp(d->line, "DO ", 3))
		return (&cub->map.door_tex.name);
	if (!ft_strncmp(d->line, "OD ", 3))
		return (&cub->map.opendoor_tex.name);
	if (!ft_strncmp(d->line, "SK ", 3))
		return (&cub->map.sky_tex.name);
	return (get_sprite_name_ptr(cub, d));
}

int	get_texture(t_cub *cub, t_pars_data *d)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	if (empty_line(d->line))
		return (1);
	i = 2;
	while (d->line[i] && d->line[i] == ' ')
		i++;
	name = get_name_ptr(cub, d);
	if (!name)
		return (1);
	if (*name)
		return (2);
	*name = gc_strtrim(&(d->line[i]), " \n");
	if (ft_strcmp(&(*name)[ft_strlen(*name) - 4], ".xpm"))
		return (free2(*name), *name = NULL, 4);
	fd_tex = open(*name, O_RDONLY);
	if (fd_tex == -1)
		return (free2(*name), 3);
	return (close(fd_tex), 0);
}
