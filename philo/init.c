/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:36:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/24 14:12:42 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	fill_table_value(t_dinner *dinner, int ac, char **av)
{
	dinner->table->end = 0;
	dinner->table->to_eat = -1;
	dinner->table->nb_of_philo = ft_atoi(av[1]);
	dinner->table->time_to_die = ft_atoi(av[2]);
	dinner->table->time_to_eat = ft_atoi(av[3]);
	dinner->table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		dinner->table->to_eat = ft_atoi(av[5]);
	if (dinner->table->nb_of_philo < 1
		|| dinner->table->time_to_die < 0
		|| dinner->table->time_to_sleep < 0
		|| dinner->table->time_to_eat < 0
		|| (ac == 6 && dinner->table->to_eat < 0))
		return (1);
	return (0);
}

int	init_table(t_dinner *dinner, int ac, char **av)
{
	dinner->table = malloc(sizeof(t_table));
	if (!dinner->table)
		return (1);
	memset(dinner->table, 0, sizeof(t_table));
	if (fill_table_value(dinner, ac, av))
		quit("Invalid argument\n", dinner);
	pthread_mutex_init(&dinner->table->end_lock, NULL);
	pthread_mutex_init(&dinner->table->write_lock, NULL);
	return (0);
}

static int	fill_philo(t_dinner *dinner)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = dinner->philo;
	while (++i < dinner->table->nb_of_philo)
	{
		memset(&philo[i], 0, (sizeof(t_philo)));
		philo[i].id = i + 1;
		philo[i].nb_of_meal = 0;
		philo[i].table = dinner->table;
		philo[i].l_fork = malloc(sizeof(pthread_mutex_t));
		if (!philo[i].l_fork)
		{
			while (i--)
				free(philo[i].l_fork);
			free(philo);
			return (1);
		}
		pthread_mutex_init(philo[i].l_fork, NULL);
		pthread_mutex_init(&philo[i].eat_lock, NULL);
	}
	return (0);
}

int	init_philo(t_dinner *dinner, int nb_philo)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * nb_philo);
	if (!philo)
		return (1);
	dinner->philo = philo;
	if (fill_philo(dinner))
		return (1);
	i = 0;
	while (i < nb_philo)
	{
		if (nb_philo == 1)
			philo[i].r_fork = NULL;
		else if (i != (nb_philo - 1))
			philo[i].r_fork = philo[i + 1].l_fork;
		else
			philo[i].r_fork = philo[0].l_fork;
		i++;
	}
	return (0);
}
