/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:27:26 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:27:27 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	*ft_min_arr(int *arr, size_t len)
{
	size_t	i;
	int		*min;

	if (!arr)
		return ((void *)0);
	min = &arr[0];
	i = 1;
	while (i < len)
	{
		if (arr[i] < *min)
			min = &arr[i];
		i++;
	}
	return (min);
}
