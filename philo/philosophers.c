/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:15:08 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/03 16:44:28 by blaurent         ###   ########.fr       */
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
void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf("Hey ! I'm philo nb %d\n", philo->id);
	return (NULL);
}

int begin_simulation(t_dinner *dinner)
{
	int	i;

	i = -1;
	while (++i < dinner->table->nb_of_philo)
	{
		if (pthread_create(&dinner->philo[i].thread, NULL, philosopher, &dinner->philo[i]))
		{
			return (1);
		}
		usleep(1000);
		pthread_detach(dinner->philo[i].thread);
	}
	return (0);
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (ac < 5 || 6 < ac)
		return (EXIT_FAILURE);
	dinner = malloc(sizeof(*dinner));
	if (!dinner)
		return (EXIT_FAILURE);
	// memset(dinner, 0, sizeof(t_dinner));
	if (init_table(dinner, ac, av))
		return (EXIT_FAILURE);
	if (init_philo(dinner, dinner->table->nb_of_philo))
		return (EXIT_FAILURE);
	if (!begin_simulation(dinner))
		return (EXIT_FAILURE);
	free(dinner->philo);
	free(dinner->table);
	free(dinner);
	return (EXIT_SUCCESS);
}
