/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:03:57 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 13:04:15 by bazaluga         ###   ########.fr       */
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
		return (ft_strdup2(s2));
	else if (!s2)
		return (ft_strdup2(s1));
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
