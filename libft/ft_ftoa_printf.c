/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga <bazaluga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 12:43:27 by bazaluga          #+#    #+#             */
/*   Updated: 2025/01/06 14:00:41 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static size_t	n_size(long int_part)
{
	size_t	size;

	size = 1;
	while (int_part > 9)
	{
		size++;
		int_part /= 10;
	}
	return (size);
}

static void	round_str(char *res, double remainder, size_t end)
{
	if ((int)(remainder * 10) >= 5)
		res[end]++;
	while (end > 0 && res[end] != '.' && res[end] > '9')
	{
		res[end] = '0';
		res[end - 1]++;
		end--;
	}
}

static void	convert(char *res, double n, unsigned long int_part, size_t *sizes)
{
	size_t	i;
	size_t	len;

	len = sizes[0];
	i = sizes[0] - sizes[1];
	n -= int_part;
	while (sizes[0] > 0 && sizes[1] > 0)
	{
		n *= 10;
		res[i] = (int)n + '0';
		n -= (int)n;
		i++;
		sizes[1]--;
		sizes[0]--;
		if (sizes[1] == 0)
			res[--sizes[0]] = '.';
	}
	while (sizes[0] > 0)
	{
		res[sizes[0] - 1] = int_part % 10 + '0';
		int_part /= 10;
		sizes[0]--;
	}
	round_str(res, n, len - 1);
}

char	*ft_ftoa_printf(double n, int precision, t_flags *f)
{
	double	int_part;
	int		neg;
	size_t	sizes[2];
	char	*res;

	if (precision < 0)
		return (NULL);
	sizes[1] = precision;
	neg = 0;
	if (n < 0 && ++neg)
		n *= -1;
	int_part = (unsigned long)n;
	sizes[0] = n_size(int_part);
	sizes[0] += (neg || f->plus) + precision + (1 * (precision > 0));
	res = (char *)ft_calloc(sizes[0] + 1, sizeof(char));
	if (!res)
		return (NULL);
	convert(res, n, int_part, sizes);
	if (neg)
		res[0] = '-';
	if (f->plus && !neg)
		res[0] = '+';
	return (res);
}
