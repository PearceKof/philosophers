/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:35:47 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/24 15:03:16 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_alone(t_philo *philo)
{
	while (!dinner_stopped(philo->table))
	{
		pthread_mutex_lock(philo->l_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_unlock(philo->l_fork);
		print_state(philo, "is sleeping");
		ft_usleep(philo->table, philo->table->time_to_sleep);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

static void	philo_eat(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork");
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = get_time();
	if (philo->table->to_eat != -1)
		philo->nb_of_meal++;
	pthread_mutex_unlock(&philo->eat_lock);
	ft_usleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	philo_think(t_philo *philo)
{
	time_t	time_to_think;
	time_t	last_meal;

	pthread_mutex_lock(&philo->eat_lock);
	last_meal = get_time() - philo->last_meal;
	time_to_think = (philo->table->time_to_die
			- last_meal - philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->eat_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 500)
		time_to_think = 500;
	print_state(philo, "is thinking");
	ft_usleep(philo->table, time_to_think);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->eat_lock);
	if (philo->table->to_eat == 0)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (NULL);
	}
	philo->last_meal = philo->table->dinner_start;
	pthread_mutex_unlock(&philo->eat_lock);
	wait_start(philo->table->dinner_start);
	if (philo->table->nb_of_philo == 1)
		return (philo_alone(philo));
	if (philo->id % 2 == 0)
		ft_usleep(philo->table, (philo->table->time_to_eat / 2));
	while (!dinner_stopped(philo->table))
	{
		philo_eat(philo);
		print_state(philo, "is sleeping");
		ft_usleep(philo->table, philo->table->time_to_sleep);
		philo_think(philo);
	}
	return (NULL);
}
