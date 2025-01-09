/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:59:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/09 20:52:54 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

char	*ft_strtrim_free(const char *str, const char *charset)
{
	char	*new;

	new = ft_strtrim(str, charset);
	free((char *)str);
	return (new);
}

int	check_infos(t_cub *cub)
{
	t_map	*map;

	map = &cub->map;
	if (!map->tex_nor.name || !map->tex_sou.name || !map->tex_eas.name
		|| !map->tex_wes.name)
		return (1);
	if (map->ceil_set && map->tex_ceil.name)
		return (2);
	if (map->floor_set && map->tex_floor.name)
		return (3);
	map->ceil_set = (map->ceil_set || map->tex_ceil.name != NULL);
	map->floor_set = (map->floor_set || map->tex_floor.name != NULL);
	map->sky_set = (map->tex_sky.name != NULL);
	if (!map->ceil_set && !map->sky_set)
		return (4);
	if (!map->floor_set)
		return (5);
	if (map->ceil_set && map->sky_set)
		return (6);
	if (map->tex_door.name && !map->tex_opendoor.name)
		return (7);
	if (!map->tex_door.name && map->tex_opendoor.name)
		return (8);
	return (0);
}
