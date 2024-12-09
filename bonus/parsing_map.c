/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/10 00:43:45 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
			cub->player.pos.x = i + 0.5;
			cub->player.pos.y = 0;
			cub->player.pos.z = row + 0.5;
			line[i] = EMPTY;
		}
		i++;
	}
	return (i);
}

static bool	add_line_to_lines(t_list *line, char **raw, size_t len_line)
{
	size_t	act_len;

	act_len = ft_strlen((const char *)(line->content));
	if (act_len < len_line)
	{
		*raw = gc_calloc(len_line + 1, sizeof(char));
		if (!*raw)
			return (false);
		ft_strlcpy(*raw, (const char *)line->content, act_len + 1);
		ft_memset(&(*raw)[act_len], ' ', len_line - act_len);
		free2(line->content);
	}
	else
		*raw = (char *)(line->content);
	return (true);
}

static bool	lst_to_map(t_cub *cub, t_list *lines, int size)
{
	t_list	*node;
	int		i;
	size_t	len_line;

	len_line = lst_get_maxstr(lines);
	cub->map.width = len_line;
	cub->map.raw = (char **)gc_calloc(size + 1, sizeof(char *));
	if (!cub->map.raw)
		return (false);
	i = 0;
	while (lines)
	{
		node = lines;
		lines = lines->next;
		if (!add_line_to_lines(node, &cub->map.raw[i], len_line))
			return (false);
		free2(node);
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
	//add verif: if ! door_tex && (D || O) in map => error
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
