/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/13 18:36:22 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "libft.h"

static int	save_sprite(t_cub *cub, t_pars_data *d, int row, int col)
{
	//lst_addback to d->lstsprites with row & i as position
}

static int	check_map_line(t_cub *cub, t_pars_data *d, int row)
{
	size_t	i;

	i = 0;
	while (d->line[i] && d->line[i] != '\n')
	{
		if (ft_strchr(d->names, d->line[i]))
			return (save_sprite(cub, d, row, i));
		if (!ft_strchr(MAPCHARS, d->line[i]))
			return (0);
		if (d->line[i] == N || d->line[i] == S
			|| d->line[i] == E || d->line[i] == W)
		{
			if (cub->player.spd > 0 || row == 0 || i == 0 || !d->line[i + 1])
				return (0);
			cub->player.rot = (M_PI / 2 * (d->line[i] == S))
				+ (M_PI * (d->line[i] == E)) + (1.5 * M_PI * (d->line[i] == N));
			cub->player.spd = 3;
			cub->player.pos.x = i + 0.5;
			cub->player.pos.y = 0;
			cub->player.pos.z = row + 0.5;
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

	if (!line)
		skip_empty_lines(fd, &line);
	while (line)
	{
		i_end = check_map_line(cub, line, cub->map.height);
		if (!i_end)
			break ;
		line[i_end] = 0;
		trash_add(line, &free);
		if (!ft_lstadd_back(lines, gc_lstnew(line)))
			return (close(fd), 2);
		line = get_next_line(fd);
		cub->map.height++;
	}
	skip_empty_lines(fd, &line);
	if (line)
		return (close(fd), free(line), 3);
	return (cub->player.spd == 0);
}

int	get_map(t_cub *cub, int fd, char *line)
{
	t_list	*lines;
	int		res;

	lines = NULL;
	res = get_lstmap(cub, fd, &lines, line);
	if (res)
		return (res);
	return (lst_to_map(cub, lines, cub->map.height));
}
