/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:28:43 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/23 23:20:55 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "libft.h"
#include <fcntl.h>

static void	get_next_num(char **line, bool last)
{
	while (**line && **line == ' ')
		(*line)++;
	if ((!last && **line != ',') || (last && **line))
		*line = NULL;
	else if (!last)
		(*line)++;
}

static bool	get_colour_component(char **line, unsigned char *c)
{
	long long	res;
	char		*end;

	res = ft_strtoll(*line, &end, 10);
	if (res < 0 || res > 255 || *line == end)
		return (false);
	*c = (unsigned char)res;
	*line = *line + (end - *line);
	return (true);
}

static bool	get_colour(t_cub *cub, char *line, char part)
{
	t_trgb		rgb;

	rgb = (t_trgb){0};
	if (!get_colour_component(&line, &rgb.r))
		return (false);
	get_next_num(&line, false);
	if (!line)
		return (false);
	if (!get_colour_component(&line, &rgb.g))
		return (false);
	get_next_num(&line, false);
	if (!line)
		return (false);
	if (!get_colour_component(&line, &rgb.b))
		return (false);
	get_next_num(&line, true);
	if (!line)
		return (false);
	if (part == 'C')
		cub->map.col_ceil = rgbtou(rgb);
	else if (part == 'F')
		cub->map.col_floor = rgbtou(rgb);
	return (true);
}

static bool	get_texture(t_cub *cub, char *line)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	name = NULL;
	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_strncmp(line, "NO ", 3))
		name = &cub->map.tex_nor_name;
	else if (!ft_strncmp(line, "SO ", 3))
		name = &cub->map.tex_sou_name;
	else if (!ft_strncmp(line, "WE ", 3))
		name = &cub->map.tex_wes_name;
	else if (!ft_strncmp(line, "EA ", 3))
		name = &cub->map.tex_eas_name;
	if (*name)
		return (false);
	*name = gc_strtrim(&line[i], " \n");
	if (ft_strcmp(&(*name)[ft_strlen(*name) - 4], ".xpm"))
		return (free2(*name), *name=NULL, false);
	fd_tex = open(*name, O_RDONLY);
	if (fd_tex == -1)
		return (free2(*name), false);
	return (close(fd_tex),true);
}

int	get_infos(t_cub *cub, int fd, int *infos_count)
{
	char	*line;

	*infos_count = 0;
	line = ft_strtrim_free(get_next_line(fd), " \n");
	while (line && *infos_count < 6)
	{
		if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		{
			if (!get_texture(cub, line))
				return (close(fd), free(line), 2);
			(*infos_count)++;
		}
		else if (!ft_strncmp(line, "F ", 2) || (!ft_strncmp(line, "C ", 2)))
		{
			if (!get_colour(cub, line + 2, line[0]))
				return (close(fd), free(line), 3);
			(*infos_count)++;
		}
		else if (!empty_line(line))
			return (close(fd), free(line), 4);
		free(line);
		line = ft_strtrim_free(get_next_line(fd), " \n");
	}
	return (!(*infos_count == 6));
}
