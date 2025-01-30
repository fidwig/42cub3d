/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/30 13:18:00 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "libft.h"

static int	check_map_line(t_cub *cub, t_pars_data *d, int row)
{
	size_t	i;

	i = 0;
	while (d->line[i] && d->line[i] != '\n')
	{
		if (ft_strchr(d->names, d->line[i]) && !save_sprite(d, row, i))
			return (0);
		if (!ft_strchr(MAPCHARS, d->line[i]))
			return (0);
		if (ft_strchr("NSEW", d->line[i]))
		{
			if (cub->player.spd > 0 || row == 0 || i == 0
				|| d->line[i + 1] == '\n')
				return (0);
			cub->player.rot = (M_PI / 2 * (d->line[i] == S))
				+ (M_PI * (d->line[i] == W)) + (1.5 * M_PI * (d->line[i] == N));
			cub->player.spd = 3;
			cub->player.pos = (t_dvec3){i + 0.5, 0, row + 0.5};
			d->line[i] = EMPTY;
		}
		i++;
	}
	return (i);
}

static void	skip_empty_lines(int fd, char **line)
{
	if (!*line)
		*line = get_next_line(fd);
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

static int	get_lstmap(t_cub *cub, int fd, t_list **lines, t_pars_data *d)
{
	int		i_end;

	if (!d->line)
		skip_empty_lines(fd, &d->line);
	while (d->line)
	{
		i_end = check_map_line(cub, d, cub->map.height);
		if (!i_end)
			break ;
		d->line[i_end] = 0;
		trash_add(d->line, &free);
		if (!ft_lstadd_back(lines, gc_lstnew(d->line)))
			return (close(fd), 2);
		d->line = get_next_line(fd);
		cub->map.height++;
	}
	skip_empty_lines(fd, &d->line);
	if (d->line)
		return (close(fd), free(d->line), d->line = NULL, 3);
	return (cub->player.spd == 0);
}

int	get_map(t_cub *cub, t_pars_data *d)
{
	t_list	*lines;
	int		res;

	lines = NULL;
	res = get_lstmap(cub, d->fd, &lines, d);
	if (res)
		return (res);
	res = lst_to_map(cub, lines, cub->map.height);
	if (res)
		return (res);
	res = lst_to_sprites(cub, d);
	return (res);
}
