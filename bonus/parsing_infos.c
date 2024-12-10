/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:28:43 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/10 15:13:36 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
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
		cub->map.ceil_col = rgbtou(rgb);
	else if (part == 'F')
		cub->map.floor_col = rgbtou(rgb);
	else
		return (false);
	return (true);
}

int	get_infos(t_cub *cub, int fd, int *infos_count, char **line)
{
	/* char	*line; */
	int		got_tex;

	*infos_count = 0;
	*line = ft_strtrim_free(get_next_line(fd), " \n");
	while (line && *infos_count < 8)
	{
		got_tex = get_texture(cub, *line);
		if (!got_tex && !empty_line(*line))
			return (4);//be careful : close fd & free line if  needed in parse_scene
		else if (got_tex == -1
			&& (!ft_strncmp(*line, "C ", 2) || !ft_strncmp(*line, "F ", 2)))
		{
			if (!get_colour(cub, (*line) + 2, (*line)[0]))
				return (close(fd), free(*line), 3);
			(*infos_count)++;
		}
		else if (got_tex == -1)
			return (close(fd), free(*line), 2);
		else if (got_tex)
			(*infos_count)++;
		free(*line);
		*line = ft_strtrim_free(get_next_line(fd), " \n");
	}
	return (1);
}
