/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr >           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:29:48 by jsommet           #+#    #+#             */
/*   Updated: 2023/11/15 15:52:19 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_len(long n)
{
	int		l;

	l = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n = -n;
		l++;
	}
	while (n > 0)
	{
		l++;
		n = n / 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	long	ln;
	char	*s;
	int		l;

	ln = (long) n;
	l = itoa_len(ln);
	s = (char *) malloc((l + 1) * sizeof(char));
	if (!s)
		return (NULL);
	s[l] = '\0';
	if (ln == 0)
		s[0] = '0';
	if (ln < 0)
	{
		s[0] = '-';
		ln = -ln;
	}
	while (ln > 0)
	{
		s[--l] = '0' + (ln % 10);
		ln = ln / 10;
	}
	return (s);
}
