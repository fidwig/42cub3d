/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:46:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/23 11:18:45 by bazaluga         ###   ########.fr       */
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

static char	**get_sprite_name_ptr(t_pars_data *d, char *line)
{
	int			i;

	if (!ft_strncmp(line, "S_", 2) && line[2])
	{
		if (line[2] >= 'a' && line[2] <= 'z' && (line[3] == ' '
				|| line[3] == '\n'))
		{
			i = 0;
			while (d->names[i])
			{
				if (d->names[i] == line[2])
					return (NULL);
				i++;
			}
			if (i == 26)
				return (NULL);
			d->sprites[i].name = line[2];
			d->names[i] = line[2];
			if (!config_sprite(d, &d->sprites[i]))
				return (NULL);
			return (&d->sprites[i].tex.name);
		}
	}
	return (NULL);
}

static char	**get_name_ptr(t_cub *cub, t_pars_data *d, size_t *i)
{
	*i = *i + 2;
	if (!ft_strncmp(&d->line[*i - 2], "NO ", 3))
		return (&cub->map.nor_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "SO ", 3))
		return (&cub->map.sou_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "WE ", 3))
		return (&cub->map.wes_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "EA ", 3))
		return (&cub->map.eas_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "F ", 2))
		return (&cub->map.floor_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "DO ", 3))
		return (&cub->map.door_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "OD ", 3))
		return (&cub->map.opendoor_tex.name);
	if (!ft_strncmp(&d->line[*i - 2], "SK ", 3))
		return (&cub->map.sky_tex.name);
	*i += 1;
	return (get_sprite_name_ptr(d, &d->line[*i - 3]));
}

int	get_texture(t_cub *cub, t_pars_data *d, char *line)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	if (empty_line(line))
		return (1);
	i = line - d->line;
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
