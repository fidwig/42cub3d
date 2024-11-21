/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:59:18 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/21 21:26:23 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "get_next_line.h"
#include "libft.h"

static bool	empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

static int	check_map_line(t_cub *cub, char *line, int row)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(MAPCHARS, line[i++]))
			return (0);
		if (line[i] >= N && line[i] <= W)
		{
			if (row == 0 || i == 0 || !line[i + 1])
				return (false);
			cub->player.rot = (M_PI/2 * (line[i] == N)) + (M_PI * (line[i] == W))
			+ (-M_PI/2 * (line[i] == S));
			cub->player.spd = 10;
			cub->player.pos.x = i;
			cub->player.pos.y = row;
			cub->player.pos.z = 0;
		}
	}
	return (i);
}

static bool	lst_to_map(t_cub *cub, t_list *lines, int size)
{
	t_list	*node;
	int		len;
	int		i;

	cub->map.raw = (char **)ft_calloc(size, sizeof(char *));
	if (!cub->map.raw)
		return (false);
	i = 0;
	while (lines)
	{
		node = lines;
		lines = lines->next;
		cub->map.raw[i] = node->content;
		free2(node);
		i++;
	}
	return (true);
}

static void skip_empty_lines(int fd, char **line)
{
	if (!*line)
		*line = get_next_line(fd);
	while (*line && empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

bool	get_map(t_cub *cub, int fd)
{
	char	*line;
	int		i_end;
	t_list	*lines;
	int		size;

	lines = NULL;
	line = NULL;
	skip_empty_lines(fd, &line);
	size = 0;
	while (line)
	{
		i_end = check_map_line(cub, line, size);
		if (!i_end)
			break ;
		line[i_end] = 0;
		trash_add(line, &free);
		if (!ft_lstadd_back(&lines, gc_lstnew(line)))
			return (false);
		size++;
	}
	skip_empty_lines(fd, &line);
	if (line)
		return (free(line), false);
	if (!lst_to_map(cub, lines, size))
		return (false);
	return (true);
}
