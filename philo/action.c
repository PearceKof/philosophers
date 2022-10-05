/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:26:48 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/05 16:59:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo->table->dinner_started = 1;
	print_state(philo, "has taken a fork (l)");
	pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork(r)");
	print_state(philo, "is eating");
	ft_usleep(philo->table, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_state(philo, "end eating");
}