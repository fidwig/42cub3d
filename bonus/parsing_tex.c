/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:46:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/06 14:24:33 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static char	**get_name_ptr(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (&cub->map.nor_tex.name);
	if (!ft_strncmp(line, "SO ", 3))
		return (&cub->map.sou_tex.name);
	if (!ft_strncmp(line, "WE ", 3))
		return (&cub->map.wes_tex.name);
	if (!ft_strncmp(line, "EA ", 3))
		return (&cub->map.eas_tex.name);
	if (!ft_strncmp(line, "C ", 2))
		return (&cub->map.ceil_tex.name);
	if (!ft_strncmp(line, "F ", 2))
		return (&cub->map.floor_tex.name);
	if (!ft_strncmp(line, "DO ", 3))
		return (&cub->map.door_tex.name);
	if (!ft_strncmp(line, "OD ", 3))
		return (&cub->map.opendoor_tex.name);
	return (NULL);
}

int	get_texture(t_cub *cub, char *line)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	if (empty_line(line))
		return (0);
	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	name = get_name_ptr(cub, line);
	if (!name)
		return (0);
	if (*name)
		return (-1);
	*name = gc_strtrim(&line[i], " \n");
	if (ft_strcmp(&(*name)[ft_strlen(*name) - 4], ".xpm"))
		return (free2(*name), *name = NULL, -1);
	fd_tex = open(*name, O_RDONLY);
	if (fd_tex == -1)
		return (free2(*name), -1);
	return (close(fd_tex), 1);
}
