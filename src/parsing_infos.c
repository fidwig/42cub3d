/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:28:43 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/21 15:12:15 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	get_color(t_cub *cub, char *line, char part)
{
	t_trgb		rgb;
	char		*end;

	rgb = (t_trgb){0};
	end = line;
	rgb.r = ft_strtoll(line, &end, 10);
	if (rgb.r < 0 || rgb.r > 255 || line == end || (*end != ' ' && *end != ','))
		return (free(line), stop_error(1, cub, "Bad floor/ceil color"), false);
	while (*end && *end != ',')
		end++;
	end += (*end == ',');
	rgb.g = ft_strtoll(line + (end - line), &end, 10);
	if (rgb.g < 0 || rgb.g > 255 || line == end || (*end != ' ' && *end != ','))
		return (free(line), stop_error(1, cub, "Bad floor/ceil color"), false);
	while (*end && *end != ',')
		end++;
	end += (*end == ',');
	rgb.b = ft_strtoll(line + (end - line), &end, 10);
	if (rgb.b < 0 || rgb.b > 255 || line == end || (*end != ' ' && *end != ','))
		return (free(line), stop_error(1, cub, "Bad floor/ceil color"), false);
	if (part == 'C')
		cub->map.col_ceil = rgbtou(rgb);
	if (part == 'F')
		cub->map.col_floor = rgbtou(rgb);
	return (true);
}

static bool	get_texture(t_cub *cub, char *line)
{
	size_t	i;
	t_image	*tex_img;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_strncmp(line, "NO ", 3))
		tex_img = &cub->map.tex_nor;
	if (!ft_strncmp(line, "SO ", 3))
		tex_img = &cub->map.tex_sou;
	if (!ft_strncmp(line, "WE ", 3))
		tex_img = &cub->map.tex_wes;
	if (!ft_strncmp(line, "EA ", 3))
		tex_img = &cub->map.tex_eas;
	tex_img->img = mlx_xpm_file_to_image(cub->mlx, &line[i],
		&cub->image.width, &cub->image.height);
	//get_data_addr
	return (tex_img->img != NULL);
}

int	get_infos(t_cub *cub, int fd)
{
	char	*line;
	int		infos_count;

	infos_count = 0;
	line = get_next_line(fd);
	while (line && infos_count < 6)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		{
			if (!get_texture(cub, line))
				return (free(line), 2);
			infos_count++;
		}
		else if (!ft_strncmp(line, "F ", 2) || (!ft_strncmp(line, "C ", 2)))
		{
			if (!get_color(cub, line, line[0]))
				return (free(line), 3);//display diff. msg with the returns
			infos_count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (!(infos_count == 6));
}
