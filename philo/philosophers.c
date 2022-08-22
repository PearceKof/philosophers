/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:08 by blaurent          #+#    #+#             */
/*   Updated: 2022/08/22 15:37:22 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/
int	main(int ag, char **av)
{
	t_philo	*philo;

	if (ag < 4 || ag > 7)
		return (EXIT_FAILURE);
	philo = init_philo(ag, av);
	return (EXIT_SUCCESS);
}
