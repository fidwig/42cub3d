/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:28:43 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/18 13:22:27 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "typedefs_bonus.h"
#include <fcntl.h>

static void	get_next_num(char **line, bool last)
{
	while (**line && **line == ' ')
		(*line)++;
	if ((!last && **line != ',') || (last && **line && **line != '\n'))
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
	t_trgb			rgb;
	unsigned char	*ptr;

	if ((part == 'C' && cub->map.ceil_set)
		|| (part == 'F' && cub->map.floor_set))
		return (false);
	rgb = (t_trgb){0};
	ptr = &rgb.r;
	while (ptr >= &rgb.b)
	{
		if (!get_colour_component(&line, ptr))
			return (false);
		get_next_num(&line, (ptr == &rgb.b));
		if (!line)
			return (false);
		ptr -= sizeof(unsigned char);
	}
	if (part == 'C')
		cub->map.ceil_set = ((cub->map.ceil_col = rgbtou(rgb)) || true);
	else
		cub->map.floor_set = ((cub->map.floor_col = rgbtou(rgb)) || true);
	return (true);
}

static int	infos_handle_line(t_cub *cub, t_pars_data *d)
{
	int		got_tex;
	char	*line;

	line = d->line;
	while (*line && *line == ' ')
		line++;
	got_tex = get_texture(cub, d);
	if (!got_tex)
		return (0);
	if (got_tex > 1 && got_tex <= 3)
		return (got_tex);
	if (!ft_strncmp(line, "C ", 2) || !ft_strncmp(line, "F ", 2))
	{
		if (!get_colour(cub, (line) + 2, (line)[0]))
			return (4);
		return (0);
	}
	while (*line && *line != '\n')
	{
		if (!ft_strchr(MAPCHARS, *line))
			return (1);
		line++;
	}
	return (5);
}

int	get_infos(t_cub *cub, t_pars_data *d)
{
	int		infos_count;
	int		res;

	infos_count = 0;
	d->line = get_next_line(d->fd);
	while (d->line && infos_count < 34)
	{
		if (empty_line(d->line))
		{
			free(d->line);
			d->line = get_next_line(d->fd);
			continue ;
		}
		res = infos_handle_line(cub, d);
		if (res && res < 5)
			return (close(d->fd), free(d->line), d->line = NULL, res);
		else if (res && res == 5)
			return (res);
		infos_count++;
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	return (free(d->line), d->line = NULL, 0);
}
