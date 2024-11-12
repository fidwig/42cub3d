/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:43:12 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/22 15:14:42 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			l;
	unsigned int	i;
	char			*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s) - 1)
		return (ft_strdup(""));
	l = ft_strlen((char *)(s + start));
	if (len < l)
		l = len;
	sub = (char *) malloc((l + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < l && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
