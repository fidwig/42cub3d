/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:59:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/09 14:56:15 by bazaluga         ###   ########.fr       */
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
	//check if ceil/floor duplicates (tex + col)
	//set the correct bools
	//check if ceil + sky (error)
	//
	/* if (!map->ceil_set && !map->sky_set) */
	/* 	return (2); */
	/* if (map->ceil_set && map->sky_set) */
	/* 	return (3); */
	/* if (!map->floor_set) */
	/* 	return (4); */
	if (map->tex_door.name && !map->tex_opendoor.name)
		return (5);
	if (!map->tex_door.name && map->tex_opendoor.name)
		return (6);
	return (0);
}
