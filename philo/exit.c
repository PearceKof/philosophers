/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:44:21 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/19 13:53:52 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_all(t_dinner *dinner)
{
	int	i;

	if (dinner)
	{
		if (dinner->philo)
		{
			i = 0;
			while (i < dinner->table->nb_of_philo)
			{
				pthread_mutex_destroy(&dinner->philo[i].eat_lock);
				pthread_mutex_destroy(dinner->philo[i].l_fork);
				free(dinner->philo[i++].l_fork);
			}
			free(dinner->philo);
		}
		pthread_mutex_destroy(&dinner->table->end_lock);
		pthread_mutex_destroy(&dinner->table->write_lock);
		if (dinner->table)
			free(dinner->table);
		free(dinner);
	}
}

void	quit(char *error, t_dinner *dinner)
{
	free_all(dinner);
	if (error)
	{
		ft_putstr_fd(error, 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
