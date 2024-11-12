/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:27:46 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:27:46 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>

int	*ft_max_arr(int *arr, size_t len)
{
	size_t	i;
	int		*max;

	if (!arr)
		return ((void *)0);
	max = &arr[0];
	i = 1;
	while (i < len)
	{
		if (arr[i] > *max)
			max = &arr[i];
		i++;
	}
	return (max);
}
