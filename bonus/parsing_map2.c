/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 23:20:54 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/17 11:27:48 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

int	lst_to_map(t_cub *cub, t_list *lines, int size)
{
	t_list	*node;
	int		i;
	size_t	len_line;

	len_line = lst_get_maxstr(lines);
	cub->map.width = len_line;
	cub->map.raw = (char **)gc_calloc(size + 1, sizeof(char *));
	if (!cub->map.raw)
		return (4);
	i = 0;
	while (lines)
	{
		node = lines;
		lines = lines->next;
		if (!add_line_to_lines(node, &cub->map.raw[i], len_line))
			return (5);
		free2(node);
		i++;
	}
	cub->map.height = i;
	return (0);
}
