/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:45:16 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 17:45:20 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc2(size_t nmemb, size_t size)
{
	void	*s;
	size_t	i;

	i = nmemb * size;
	if (i != 0 && i / nmemb != size)
		return (NULL);
	s = malloc2(nmemb * size);
	if (!s)
		return (NULL);
	ft_bzero(s, nmemb * size);
	return (s);
}