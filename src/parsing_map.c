/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:59:18 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/27 12:34:34 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
				return (false);
			cub->player.rot = (M_PI / 2 * (line[i] == N))
				+ (M_PI * (line[i] == W)) + ((3 * M_PI) / 2 * (line[i] == S));
			cub->player.spd = 10;
			cub->player.pos.x = i;
			cub->player.pos.y = row;
			cub->player.pos.z = 0;
			line[i] = EMPTY;
		}
		i++;
	}
	return (i);
}

static bool	lst_to_map(t_cub *cub, t_list *lines, int size)
{
	t_list	*node;
	int		i;
	int		len;

	cub->map.raw = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!cub->map.raw)
		return (false);
	cub->map.width = 0;
	i = 0;
	while (lines)
	{
		node = lines;
		lines = lines->next;
		cub->map.raw[i] = node->content;
		free2(node);
		len = ft_strlen(cub->map.raw[i]);
		if (len > cub->map.width)
			cub->map.width = len;
		i++;
	}
	cub->map.height = i;
	return (true);
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
			return (close(fd), false);
		line = get_next_line(fd);
		size++;
	}
	skip_empty_lines(fd, &line);
	if (line)
		return (close(fd), free(line), false);
	return (!(cub->player.spd == 0) && lst_to_map(cub, lines, size));
}
