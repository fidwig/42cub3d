/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 01:36:54 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/20 12:32:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "mlx.h"

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

bool	get_color(t_cub *cub, char *line)
{

}

bool	get_texture(t_cub *cub, char *line)
{
	size_t	i;
	int		fd_tex;
	t_image	*tex_img;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	fd_tex = open(&line[i], O_RDONLY);
	if (fd_tex == -1)
		stop_error(1, cub, "Error\nBad texture path");
	close(fd_tex);
	if (!ft_strncmp(line, "NO ", 3))
		tex_img = &cub->map.tex_nor;
	if (!ft_strncmp(line, "SO", 3))
		tex_img = &cub->map.tex_sou;
	if (!ft_strncmp(line, "WE", 3))
		tex_img = &cub->map.tex_wes;
	if (!ft_strncmp(line, "EA", 3))
		tex_img = &cub->map.tex_eas;
	tex_img->img = mlx_xpm_file_to_image(cub->mlx, &line[i], NULL, NULL);
	return (tex_img->img != NULL);
}

bool	get_infos(t_cub *cub, int fd)
{
	char	*line;
	int		infos_count;

	infos_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO", 3)
			|| !ft_strncmp(line, "WE", 3) || !ft_strncmp(line, "EA", 3))
		{
			if (!get_texture(cub, line))
				return (false);
			infos_count++;
		}
		else if (!ft_strncmp(line, "F ", 2) || (!ft_strncmp(line, "C ", 2)))
		{
			if (!get_color(cub, line))
				return (false);
			infos_count++;
		}
		line = get_next_line(fd);
	}
	return (infos_count == 6);
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
