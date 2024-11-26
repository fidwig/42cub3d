/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:57:33 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/26 16:51:02 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_wall(char c)
{
	return (c == '1' || c == 'D' || c == 'T');
}

int	is_visible(char c)
{
	return (c == '1' || c == 'D' || c == 'O' || c == 'T');
}

int	is_door(char c)
{
	return (c == 'D' || c == 'O');
}

int	is_see_through(char c)
{
	return (c == 'O');
}

int	is_torch(char c)
{
	return (c == 'L');
}

int	is_prop(char c)
{
	return (is_torch(c) || c == 'D');
}
