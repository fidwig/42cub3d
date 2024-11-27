/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:52:10 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:52:19 by bazaluga         ###   ########.fr       */
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
		return (gc_strdup(""));
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
