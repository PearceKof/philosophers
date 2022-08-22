/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:36:18 by blaurent          #+#    #+#             */
/*   Updated: 2022/08/22 15:37:46 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*get_last(t_philo *philo)
{
	while (philo && philo->right)
		philo = philo->right;
	return (philo);
}

static t_philo	*new_philo(int nbr)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->id = nbr;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

static void	add_philo(t_philo **philo, t_philo *new)
{
	t_philo	*last;

	if (!new)
		return ;
	last = get_last(*philo);
	last->right = new;
	new->left = last;
}

t_philo	*init_philo(int ag, char **av)
{
	t_philo	*philo;
	t_philo	*last;
	int		nbr_philo;
	int		i;

	nbr_philo = ft_atoi(av[1]);
	i = 0;
	while (i++ < nbr_philo)
	{
		if (i == 1)
			philo = new_philo(i);
		else
			add_philo(&philo, new_philo(i));
		if (!philo)
			return (NULL);
	}
	last = get_last(philo);
	philo->left = last;
	last->right = philo;
	return (philo);
}
