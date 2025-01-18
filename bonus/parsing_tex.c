/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:46:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/18 11:53:11 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include <fcntl.h>

static int	config_sprite(t_pars_data *d, t_sprite *s_ptr)
{
	size_t	i;

	i = ft_strlen(d->line) - 1;
	while (i > 0 && d->line[i] && (d->line[i] == '\n' || d->line[i] == ' '))
		i--;
	s_ptr->light = (d->line[i] == '1');
	if (d->line[i] == '1' || d->line[i] == '0')
		d->line[i] = '\0';
	else if (d->line[i] != 'm')
		return (0);
	return (1);
}

static char	**get_sprite_name_ptr(t_pars_data *d)
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
			if (!config_sprite(d, &d->sprites[i]))
				return (NULL);
			return (&d->sprites[i].tex.name);
		}
	}
	return (NULL);
}

static char	**get_name_ptr(t_cub *cub, t_pars_data *d, size_t *i)
{
	*i = 2;
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
	*i = 3;
	return (get_sprite_name_ptr(d));
}

int	get_texture(t_cub *cub, t_pars_data *d)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	if (empty_line(d->line))
		return (1);
	name = get_name_ptr(cub, d, &i);
	while (d->line[i] && d->line[i] == ' ')
		i++;
	if (!name)
		return (1);
	if (*name)
		return (2);
	*name = gc_strtrim(&(d->line[i]), " \n");
	if (!*name || ft_strcmp(&(*name)[ft_strlen(*name) - 4], ".xpm"))
		return (free2(*name), *name = NULL, 4);
	fd_tex = open(*name, O_RDONLY);
	if (fd_tex == -1)
		return (free2(*name), 3);
	return (close(fd_tex), 0);
}
