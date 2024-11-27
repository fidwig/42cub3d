/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:54:46 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:54:58 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			l;
	unsigned int	i;
	unsigned int	j;
	char			*s;

	if (!s1)
		return (gc_strdup(s2));
	else if (!s2)
		return (gc_strdup(s1));
	l = ft_strlen((char *) s1) + ft_strlen((char *) s2) + 1;
	s = (char *) malloc2(l * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		s[j++] = s1[i++];
	i = 0;
	while (s2[i])
		s[j++] = s2[i++];
	s[j] = '\0';
	return (s);
}
