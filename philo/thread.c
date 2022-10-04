/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 12:47:03 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/03 12:47:03 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_start(t_dinner *dinner)
{
	while (1)
	{
			if (dinner->table->waiting)
				break;
	}
	pthread_mutex_lock(&dinner->table->write_lock);
	printf("ENDED WAITING\n");
	pthread_mutex_unlock(&dinner->table->write_lock);
}

void	*death_check(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	wait_start(dinner);
	return (NULL);
}

void	*philosopher(void *data)
{
	time_t	timestamp;
	t_philo	*philo;

	philo = (t_philo *)data;
	timestamp = get_time() - philo->table->start_dinner_time;
	// pthread_mutex_lock(&philo->table->write_lock);
	printf("[%ld] Hey ! I'm philo nb %d\n", timestamp, philo->id);
	// pthread_mutex_unlock(&philo->table->write_lock);

	// while (philo->table->end == 0)
	// {
	// 	eat(philo);
	// }
	return (NULL);
}