/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:44:04 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/11 20:12:24 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_thread(t_dinner *dinner)
{
	int	i;

	i = 0;
	dinner->table->start_dinner_time = get_time() + (dinner->table->number_of_philosopher * 10);
	while (i < dinner->table->number_of_philosopher)
	{
		if (pthread_create(&dinner->philo[i].thread, NULL, philosopher, &dinner->philo[i]))
			return (1);
		i++;
	}
	if (pthread_create(&dinner->death_checker, NULL, death_check, dinner))
		return (1);
	return (0);
}

static void	stop_thread(t_dinner *dinner)
{
	int i;

	i = 0;
	while (i < dinner->table->number_of_philosopher)
	{
		pthread_join(dinner->philo[i].thread, NULL);
		i++;
	}
	pthread_join(dinner->death_checker, NULL);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	dinner = NULL;
	if (ac < 5 || 6 < ac)
		quit("Invalid argument", NULL);
	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		quit("malloc failed", NULL);
	dinner->table = NULL;
	dinner->philo = NULL;
	if (init_table(dinner, ac, av))
		quit("init table failed", dinner);
	if (init_philo(dinner, dinner->table->number_of_philosopher))
		quit("init philo failed", dinner);
	if (create_thread(dinner))
		quit("simulation failed", dinner);
	stop_thread(dinner);
	quit(NULL, dinner);
	return (0);
}
