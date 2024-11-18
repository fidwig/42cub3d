/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:07:31 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 13:07:52 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t			l;
	unsigned int	i;
	char			*sub;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s) - 1)
		return (ft_strdup2(""));
	l = ft_strlen((char *)(s + start));
	if (len < l)
		l = len;
	sub = (char *) malloc2((l + 1) * sizeof(char));
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
