/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atou_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:42:50 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:42:50 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchr_rank(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atou_base(const char *nptr, const char *base)
{
	int				len_base;
	unsigned int	n;
	int				rank;
	size_t			i;

	if (!nptr || !base)
		return (0);
	len_base = ft_strlen(base);
	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	n = 0;
	rank = ft_strchr_rank(base, nptr[i]);
	while (nptr[i] && rank != -1)
	{
		n = n * len_base + rank;
		i++;
		rank = ft_strchr_rank(base, nptr[i]);
	}
	return (n);
}
