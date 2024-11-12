/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:44:05 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/13 16:40:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*l;
	size_t	slen;

	slen = ft_strlen((char *) s);
	i = 0;
	l = (char *) 0;
	while (i <= slen)
	{
		if (s[i] == (char) c)
			l = (char *) &(s[i]);
		i++;
	}
	return (l);
}
