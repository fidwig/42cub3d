/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:54 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/23 10:14:35 by bazaluga         ###   ########.fr       */
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

static int	check_box(char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || !map[y + 1] || !map[y][x + 1])
		return (0);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y - 1][x] == ' '
		|| map[y + 1][x] == ' ')
		return (0);
	return (1);
}

static int	check_map(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != WALL && map[y][x] != ' ' && !check_box(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_scene(t_cub *cub, char *map_name)
{
	int	fd;
	int	res;
	int	infos_count;

	if (!check_name(map_name))
		stop_error(1, cub, "Bad scene file extension");
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		stop_error(1, cub, "Can't open map file");
	res = get_infos(cub, fd, &infos_count);
	if (res == 1)
		stop_error(1, cub, "Missing texture(s) and/or colour(s)");
	if (res == 2)
		stop_error(1, cub, "Problem getting textures");
	if (res == 3)
		stop_error(1, cub, "Problem getting floor/ceil colours");
	if (res == 4)
		stop_error(1, cub, "Unexpected line while getting textures & colours");
	if (!get_map(cub, fd))
		stop_error(1, cub, "Problem getting the map");
	close(fd);
	if (!check_map(cub->map.raw))
		stop_error(1, cub, "Incorrect map");
	return (1);
}
