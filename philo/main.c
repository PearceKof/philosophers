/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:44:04 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/05 16:55:10 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->table->start_dinner_time = get_time();
	while (i < dinner->table->number_of_philosopher)
	{
		if (pthread_create(&dinner->philo[i].thread, NULL, philosopher, &dinner->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (ac < 5 || 6 < ac)
		return (EXIT_FAILURE);
	dinner = malloc(sizeof(*dinner));
	if (!dinner)
		quit("malloc failed", NULL);
	// memset(dinner, 0, sizeof(t_dinner));
	if (init_table(dinner, ac, av))
		quit("init table failed", dinner);
	if (init_philo(dinner, dinner->table->number_of_philosopher))
		quit("init philo failed", dinner);
	if (pthread_create(&dinner->death_checker, NULL, death_check, dinner))
		quit("thread failed", dinner);
	if (create_thread(dinner))
		quit("simulation failed", dinner);
	usleep(10000);
	quit(NULL, dinner);
	return (0);
}
