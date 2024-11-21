/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/21 21:27:00 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>

static bool	check_name(char *map_name)
{
	size_t	i;

	i = ft_strlen(map_name) - 4;
	if (ft_strcmp(map_name + i, ".cub"))
		return (false);
	return (true);
}

static int	check_map(char **map)
{
	//do flood_fill
}

int	parse_scene(t_cub *cub, char *map_name)
{
	int	fd;
	int	res;

	if (!check_name(map_name))
		stop_error(1, cub, "Bad map extension");
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		stop_error(1, cub, "Can't open map file");
	res = get_infos(cub, fd);
	if (res == 1)
		stop_error(1, cub, "Problem getting textures and colours");
	if (res == 2)
		stop_error(1, cub, "Problem getting textures");
	if (res == 3)
		stop_error(1, cub, "Problem getting floor/ceil colours");
	if (!get_map(cub, fd))
		stop_error(1, cub, "Problem getting the map");

	//get_map(cub, fd);
	return (1);
}
