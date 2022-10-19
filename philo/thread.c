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

static void	set_end(t_table *table)
{
	pthread_mutex_lock(&table->end_lock);
	table->end = 1;
	pthread_mutex_unlock(&table->end_lock);
}

static int	is_philo_dead(t_philo *philo)
{
	time_t	time;

	time = get_time();
	if ((time - philo->last_meal) >= philo->table->time_to_die)
	{
		set_end(philo->table);
		pthread_mutex_lock(&philo->table->write_lock);
		printf("%ld %d died\n",
			get_time() - philo->table->dinner_start, philo->id);
		pthread_mutex_unlock(&philo->table->write_lock);
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	return (0);
}

static int	end_condition(t_dinner *dinner)
{
	int	enough_meal;
	int	i;

	i = 0;
	enough_meal = 1;
	while (i < dinner->table->nb_of_philo)
	{
		pthread_mutex_lock(&dinner->philo[i].eat_lock);
		if (is_philo_dead(&dinner->philo[i]))
			return (1);
		if (dinner->table->to_eat != -1
			&& (dinner->philo[i].nb_of_meal < dinner->table->to_eat))
				enough_meal = 0;
		pthread_mutex_unlock(&dinner->philo[i++].eat_lock);
	}
	if (dinner->table->to_eat != -1 && enough_meal)
	{
		set_end(dinner->table);
		return (1);
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
	wait_start(dinner->table->dinner_start);
	while (1)
	{
		if (end_condition(dinner))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
