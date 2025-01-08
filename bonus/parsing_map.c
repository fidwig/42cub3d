/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/08 23:54:56 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "libft.h"

static int	check_map_line(t_cub *cub, char *line, int row)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr(MAPCHARS, line[i]))
			return (0);
		if (line[i] == N || line[i] == S
			|| line[i] == E || line[i] == W)
		{
			if (cub->player.spd > 0 || row == 0 || i == 0 || !line[i + 1])
				return (0);
			//problem: inverted rotations
			cub->player.rot = (M_PI / 2 * (line[i] == N))
				+ (M_PI * (line[i] == W)) + ((3 * M_PI) / 2 * (line[i] == S));
			cub->player.spd = 10;
			cub->player.pos.x = i + 0.5;
			cub->player.pos.y = 0;
			cub->player.pos.z = row + 0.5;
			line[i] = EMPTY;
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

static int	get_lstmap(t_cub *cub, int fd, t_list **lines, int *size)
{
	char	*line;
	int		i_end;

	line = NULL;
	skip_empty_lines(fd, &line);
	while (line)
	{
		i_end = check_map_line(cub, line, *size);
		if (!i_end)
			break ;
		line[i_end] = 0;
		trash_add(line, &free);
		if (!ft_lstadd_back(lines, gc_lstnew(line)))
			return (close(fd), 2);
		line = get_next_line(fd);
		(*size)++;
	}
	skip_empty_lines(fd, &line);
	if (line)
		return (close(fd), free(line), 3);
	return (cub->player.spd == 0);
}

int	get_map(t_cub *cub, int fd)
{
	t_list	*lines;
	int		size;
	int		res;

	lines = NULL;
	size = 0;
	res = get_lstmap(cub, fd, &lines, &size);
	if (res)
		return (res);
	return (lst_to_map(cub, lines, size));
}
