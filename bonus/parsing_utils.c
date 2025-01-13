/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:59:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/13 16:31:39 by bazaluga         ###   ########.fr       */
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
	if (!map->nor_tex.name || !map->sou_tex.name || !map->eas_tex.name
		|| !map->wes_tex.name)
		return (1);
	if (map->ceil_set && map->ceil_tex.name)
		return (2);
	if (map->floor_set && map->floor_tex.name)
		return (3);
	map->ceil_set = (map->ceil_set || map->ceil_tex.name != NULL);
	map->floor_set = (map->floor_set || map->floor_tex.name != NULL);
	map->sky_set = (map->sky_tex.name != NULL);
	if (!map->ceil_set && !map->sky_set)
		return (4);
	if (!map->floor_set)
		return (5);
	if (map->ceil_set && map->sky_set)
		return (6);
	if (map->door_tex.name && !map->opendoor_tex.name)
		return (7);
	if (!map->door_tex.name && map->opendoor_tex.name)
		return (8);
	return (0);
}
