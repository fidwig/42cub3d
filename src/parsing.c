/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/18 15:42:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>
#include "get_next_line.h"

bool	check_name(char *map_name)
{
	size_t	i;

	i = ft_strlen(map_name) - 4;
	if (ft_strcmp(map_name + i, ".cub"))
		return (false);
	return (true);
}

/* bool	get_map(t_cub *cub, int fd) */
/* { */
/* 	char	*line; */

/* 	line = get_next_line(fd); */
/* 	while (line) */
/* 	{ */

/* 	} */
/* } */

bool	get_textures(t_cub *cub, int fd)
{

}

int	parse_map(t_cub *cub, char *map_name)
{
	int	fd;

	if (!check_name(map_name))
		stop_error(1, cub, "Bad map extension");
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		stop_error(1, cub, "Can't open map file");
	//get_map(cub, fd);
	return (1);
}
