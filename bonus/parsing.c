/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:36:48 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/23 10:09:02 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
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
	t_pars_data		data;
	int				res;

	data = (t_pars_data){0};
	cub->pars_data = &data;
	if (!check_name(map_name))
		stop_error(1, cub, "Bad scene file extension");
	data.fd = open(map_name, O_RDONLY);
	if (data.fd == -1)
		stop_error(1, cub, "Can't open map file");
	res = get_infos(cub, &data);
	if (res && res < 5)
		stop_error(1, cub, err_txt(0, res));
	res = check_infos(cub);
	if (res)
		stop_error(1, cub, err_txt(1, res));
	res = get_map(cub, &data);
	if (res)
		stop_error(1, cub, err_txt(2, res));
	close(data.fd);
	if (!check_map(cub->map.raw))
		stop_error(1, cub, "Incorrect map");
	return (cub->pars_data = NULL, 1);
}
