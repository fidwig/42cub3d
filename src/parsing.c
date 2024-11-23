/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/23 15:26:55 by bazaluga         ###   ########.fr       */
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

static int	dfs(char **map, int x, int y)
{
	if (x < 0 || !map[x] || y < 0 || !map[x][y] || map[x][y] == MAPCHARS[SPACE])
		return (0);
	if (map[x][y] == MAPCHARS[WALL] || map[x][y] == '9')
		return (1);
	map[x][y] = '9';
	if (!dfs(map, x - 1, y))
		return (0);
	if (!dfs(map, x + 1, y))
		return (0);
	if (!dfs(map, x, y - 1))
		return (0);
	if (!dfs(map, x, y + 1))
		return (0);
	return (1);
}

static int	check_map(char **map, t_player *p)
{
	int	x;
	int	y;

	if (!dfs(map, p->pos.x, p->pos.y))
		return (0);
	x = y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0')
			{
				if (!dfs(map, x, y))
					return (0);
				x = -1;
				break ;
			}
			else
				y++;
		}
		x++;
	}
	return (1);
}

static void	reset_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '9')
				map[i][j] = MAPCHARS[EMPTY];
			j++;
		}
		i++;
	}
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
	if (res)
		close(fd);
	if (res == 1)
		stop_error(1, cub, "Problem getting textures and colours");
	if (res == 2)
		stop_error(1, cub, "Problem getting textures");
	if (res == 3)
		stop_error(1, cub, "Problem getting floor/ceil colours");
	if (!get_map(cub, fd) && close(fd))
		stop_error(1, cub, "Problem getting the map");
	close(fd);
	if (!check_map(cub->map.raw, &cub->player))
		return (0);
	reset_map(cub->map.raw);
	return (1);
}
