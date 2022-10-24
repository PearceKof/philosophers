/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:35:25 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/24 13:03:18 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(t_table *table, time_t time)
{
	time_t	end_time;

	end_time = get_time() + time;
	while (get_time() < end_time)
	{
		if (dinner_stopped(table))
			break ;
		usleep(100);
	}
}

void	wait_start(time_t start_time)
{
	while (1)
	{
		if (get_time() > start_time)
			break ;
	}
}
