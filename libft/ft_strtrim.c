/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:24:39 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/21 17:55:43 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cins(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	strim;
	unsigned int	etrim;
	unsigned int	i;
	char			*trim;

	if (!s1)
		return (NULL);
	strim = 0;
	while (ft_cins(set, s1[strim]) && s1[strim])
		strim ++;
	i = strim - 1;
	etrim = strim - 1;
	while (s1[++i])
		if (!ft_cins(set, s1[i]))
			etrim = i;
	etrim++;
	trim = (char *) malloc((etrim - strim + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	i = strim - 1;
	while (++i < etrim && s1[i])
		trim[i - strim] = s1[i];
	trim[etrim - strim] = '\0';
	return (trim);
}
