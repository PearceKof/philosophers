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
			if (dinner->table->dinner_started)
				break;
	}
}

void	*death_check(void *data)
{
	t_dinner	*dinner;
	int			i;

	dinner = (t_dinner *)data;
	wait_start(dinner);
	while (1)
	{
		i = 0;
		while(dinner->philo[i])
		{
			if (dinner->philo[i].is_dead)
			{
				print_state(dinner->philo[i], "is_dead")
			}
			i++;
		}
		// if (i == dinner->table->number_of_philosopher)
		// {
			
		// }
	}
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->table, 1);
	while (philo->table->end == 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		print_state(philo, "is thinking", NC);
	}
	return (NULL);
}