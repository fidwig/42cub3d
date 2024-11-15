/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:47:26 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/15 18:52:20 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ise(int c)
{
	return ((c >= 9 && c <= 13) || c == 0 || c == 32);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		s;
	long	n;

	i = 0;
	s = 1;
	n = 0;
	while (ft_ise(nptr[i]) && nptr[i])
		i++;
	if ((nptr[i] == '+' || nptr[i] == '-') && nptr[i])
	{
		if (nptr[i] == '-')
			s = -s;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
		n = n * 10 + (nptr[i++] - '0');
	return ((int)n * s);
}
