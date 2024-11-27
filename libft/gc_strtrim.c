/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:50 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:52:02 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

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

char	*gc_strtrim(char const *s1, char const *set)
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
	trim = (char *) malloc2((etrim - strim + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	i = strim - 1;
	while (++i < etrim && s1[i])
		trim[i - strim] = s1[i];
	trim[etrim - strim] = '\0';
	return (trim);
}
