/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:39:39 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:48:05 by bazaluga         ###   ########.fr       */
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

char	*gc_itoa(int n)
{
	long	ln;
	char	*s;
	int		l;

	ln = (long) n;
	l = itoa_len(ln);
	s = (char *) malloc2((l + 1) * sizeof(char));
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
