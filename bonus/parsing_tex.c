/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:46:27 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/04 10:46:41 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	get_texture(t_cub *cub, char *line)
{
	size_t	i;
	char	**name;
	int		fd_tex;

	name = NULL;
	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!ft_strncmp(line, "NO ", 3))
		name = &cub->map.tex_nor_name;
	else if (!ft_strncmp(line, "SO ", 3))
		name = &cub->map.tex_sou_name;
	else if (!ft_strncmp(line, "WE ", 3))
		name = &cub->map.tex_wes_name;
	else if (!ft_strncmp(line, "EA ", 3))
		name = &cub->map.tex_eas_name;
	if (*name)
		return (false);
	*name = gc_strtrim(&line[i], " \n");
	if (ft_strcmp(&(*name)[ft_strlen(*name) - 4], ".xpm"))
		return (free2(*name), *name = NULL, false);
	fd_tex = open(*name, O_RDONLY);
	if (fd_tex == -1)
		return (free2(*name), false);
	return (close(fd_tex), true);
}
