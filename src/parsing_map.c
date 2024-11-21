/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:59:18 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/21 15:16:17 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
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

static int	check_map_line(char *line)
{
	size_t	i;
	/* int		empty; */

	/* empty = 1; */
	i = 0;
	while (line[i])
	{
		/* if (line[i] != ' ' && line[i] != '\n') */
		/* 	empty = 0; */
		if (!ft_strchr(MAPCHARS, line[i++]))
			return (0);
	}
	return (i);
}

bool	get_map(t_cub *cub, int fd)
{
	char	*line;
	int		i_end;
	t_list	*lines;

	lines = NULL;
	line = get_next_line(fd);
	while (line && empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		i_end = check_map_line(line);
		if (!i_end)
			break ;//do not return bc it can be the end of the map...
		line[i_end] = 0;
		trash_add(line, &free);
		if (!ft_lstadd_back(&lines, gc_lstnew(line)))
			return (false);
	}
	while (line && empty_line(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		return (false);
	//don't forget to convert the map to cub->map.raw
	return (true);
}
