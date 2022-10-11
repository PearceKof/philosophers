/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:26:48 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/11 18:51:28 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork (1)", YELLOW);
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork (2)", YELLOW);
	print_state(philo, "is eating", GREEN);
	ft_usleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	print_state(philo, "is sleeping", BYELLOW);
	ft_usleep(philo->table, philo->table->time_to_sleep);
}

void	think_routine(t_philo *philo, int silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->eat_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time() - philo->last_meal)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->eat_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (!silent)
		print_state(philo, "is thinking", NC);
	ft_usleep(philo->table, time_to_think);
}
