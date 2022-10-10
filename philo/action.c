/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:26:48 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/10 17:22:37 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo)
{
	philo->table->dinner_started = 1;
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
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	print_state(philo, "is eating", GREEN);
	ft_usleep(philo->table, philo->table->time_to_eat);
	print_state(philo, "end eating", GREEN);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_state(philo, "is sleeping", BYELLOW);
	ft_usleep(philo->table, philo->table->time_to_sleep);
}
