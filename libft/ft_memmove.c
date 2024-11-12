/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:06:40 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/14 18:59:01 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n-- > 0)
			((unsigned char *) dest)[n] = ((unsigned char *) src)[n];
	}
	else
	{
		while (++i < n)
			((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
	}
	return (dest);
}
