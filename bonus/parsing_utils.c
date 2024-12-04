/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:59:09 by bazaluga          #+#    #+#             */
/*   Updated: 2024/12/04 10:38:09 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}

char	*ft_strtrim_free(const char *str, const char *charset)
{
	char	*new;

	new = ft_strtrim(str, charset);
	free((char *)str);
	return (new);
}
