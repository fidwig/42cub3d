/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:20 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:51:42 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int free_1, int free_2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		return (gc_strdup_free(s2, free_2));
	if (!s2 && s1)
		return (gc_strdup_free(s1, free_1));
	if (!s1 && !s2)
		return (NULL);
	new = gc_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		new[i++] = s1[j++];
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	if (free_1)
		free2((char *)s1);
	if (free_2)
		free2((char *)s2);
	return (new);
}
