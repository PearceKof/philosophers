/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:44:04 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/15 18:43:58 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_valid_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || 6 < ac)
		return (0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == '\0')
			return (0);
		while(av[i][j])
		{
			if (j == 0 && av[i][j] == '+')
				j++;
			if ((av[i][j] < 48 || 57 < av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	create_thread(t_dinner *dinner)
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
	int	i;

	i = 0;
	while (i < dinner->table->number_of_philosopher)
		pthread_join(dinner->philo[i++].thread, NULL);
	pthread_join(dinner->death_checker, NULL);
}

int	main(int ac, char **av)
{
	t_dinner	*dinner;

	if (!is_valid_arg(ac, av))
		quit("Invalid argument\n", NULL);
	dinner = malloc(sizeof(t_dinner));
	if (!dinner)
		quit("malloc failed\n", NULL);
	memset(dinner, 0, sizeof(t_dinner));
	if (init_table(dinner, ac, av))
		quit("Init table failed\n", dinner);
	if (init_philo(dinner, dinner->table->number_of_philosopher))
		quit("init philo failed\n", dinner);
	if (create_thread(dinner))
		quit("threads creation failed\n", dinner);
	stop_thread(dinner);
	quit(NULL, dinner);
}
