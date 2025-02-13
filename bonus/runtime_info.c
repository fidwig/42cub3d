/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:45:24 by jsommet           #+#    #+#             */
/*   Updated: 2025/01/18 19:42:43 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

unsigned long	timeval_to_ms(struct timeval tv)
{
	unsigned long	ms;

	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

unsigned long	timeval_to_us(struct timeval tv)
{
	unsigned long	us;

	us = tv.tv_sec * 1000000 + tv.tv_usec;
	return (us);
}

unsigned long	get_now(int unit)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (unit == USEC)
		return (timeval_to_us(now));
	if (unit == MSEC)
		return (timeval_to_ms(now));
	return (0);
}

int	init_info(t_info *info)
{
	*info = (t_info){0};
	info->start_time = get_now(MSEC);
	return (0);
}

int	update_info(t_info *info)
{
	unsigned long	frame;

	frame = get_now(MSEC) - info->start_time;
	info->delta = (frame - info->last_frame);
	while (FIXED_FRAMERATE > 0 && info->delta < 1000 / FIXED_FRAMERATE)
	{
		frame = get_now(MSEC) - info->start_time;
		info->delta = (frame - info->last_frame);
	}
	info->frame_count++;
	info->framerate = 1000.0 / info->delta;
	if (DEBUG)
		printf("%d\n", (int)info->framerate);
	info->last_frame = frame;
	return (0);
}
