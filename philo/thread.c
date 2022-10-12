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

static int	is_philo_dead(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->end_lock);
		philo->table->end = 1;
		pthread_mutex_unlock(&philo->table->end_lock);
		pthread_mutex_lock(&philo->table->write_lock);
		printf("%s[%ld] %d is dead%s\n", RED, get_time() - philo->table->start_dinner_time, philo->id, NC);
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	return (0);
}

static int	is_finished(t_dinner *dinner)
{
	int		enough_meal;
	int	i;

	i = 0;
	enough_meal = 1;
	while (i < dinner->table->number_of_philosopher)
	{
		pthread_mutex_lock(&dinner->philo[i].eat_lock);
		if (is_philo_dead(&dinner->philo[i]))
			return (1);
		if (dinner->table->to_eat != -1)
		{
			if (dinner->philo->nb_of_meal < dinner->table->to_eat)
				enough_meal = 0;
		}
		pthread_mutex_unlock(&dinner->philo[i].eat_lock);
		i++;
	}
	if (dinner->table->to_eat != -1)
	{
		if (enough_meal)
		{
			print_state(dinner->philo, "ate enough", RED);
			return (1);
		}
	}
	return (0);
}

void	*death_check(void *data)
{
	t_dinner	*dinner;

	dinner = (t_dinner *)data;
	if (dinner->table->to_eat == 0)
		return (NULL);
	pthread_mutex_lock(&dinner->table->end_lock);
	dinner->table->end = 0;
	pthread_mutex_unlock(&dinner->table->end_lock);
	wait_start(dinner->table->start_dinner_time);
	while (1)
	{
		if (is_finished(dinner))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
