/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:28:43 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/09 14:53:56 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"
#include "typedefs_bonus.h"
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
	t_trgb			rgb;
	unsigned char	*ptr;

	rgb = (t_trgb){0};
	ptr = &rgb.r;
	while (ptr >= &rgb.b) //TEST THIS BC I DID IT VITEUF
	{
		if (!get_colour_component(&line, ptr))
			return (false);
		get_next_num(&line, false);
		if (!line)
			return (false);
		ptr -= sizeof(unsigned char);
	}
	/* if (!get_colour_component(&line, &rgb.r)) */
	/* 	return (false); */
	/* get_next_num(&line, false); */
	/* if (!line) */
	/* 	return (false); */
	/* if (!get_colour_component(&line, &rgb.g)) */
	/* 	return (false); */
	/* get_next_num(&line, false); */
	/* if (!line) */
	/* 	return (false); */
	/* if (!get_colour_component(&line, &rgb.b)) */
	/* 	return (false); */
	/* get_next_num(&line, true); */
	/* if (!line) */
	/* 	return (false); */
	//check if correct condition (missing parenthesis to win a line)
	if ((part == 'C' && cub->map.ceil_set) || part == 'F' && cub->map.floor_set)
		return (false);
	if (part == 'C')
	{
		cub->map.col_ceil = rgbtou(rgb);
		cub->map.ceil_set = true;
		return (true);
	}
	cub->map.col_floor = rgbtou(rgb);
	cub->map.floor_set = true;
	return (true);
}

static int	infos_handle_line(t_cub *cub, char *line)
{
	int	got_tex;

	got_tex = get_texture(cub, line);

	if (!got_tex)
		return (0);
	if (got_tex > 0 && got_tex <= 3)
		return (got_tex);
	/* if (got_tex == 1) */
	/* 	return (3); */
	/* if (got_tex == 2) */
	/* 	return (4); */
	/* if (got_tex == 3) */
	/* 	return (5); */
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

int	get_infos(t_cub *cub, int fd, char **line)
{
	int		infos_count;
	int		got_tex;
	int		res;

	infos_count = 0;
	*line = ft_strtrim_free(get_next_line(fd), " \n");
	while (*line && infos_count < 9)
	{
		if (empty_line(*line))
		{
			free(*line);
			*line = ft_strtrim_free(get_next_line(fd), " \n");
			continue ;
		}
		res = infos_handle_line(cub, *line);
		if (res && res < 5)
			return (close(fd), free(*line), res);
		else if (res && res == 5)
			return (res);
		infos_count++;
		free(*line);
		*line = ft_strtrim_free(get_next_line(fd), " \n");
	}
	return (free(*line), 0);
}
