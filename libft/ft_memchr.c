/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:00:00 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/12 21:58:36 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ucs;

	i = 0;
	ucs = (unsigned char *) s;
	while (i < n)
	{
		if (ucs[i] == (unsigned char) c)
			return ((void *)(ucs + i));
		i++;
	}
	return (0);
}
