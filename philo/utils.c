/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:22:19 by blaurent          #+#    #+#             */
/*   Updated: 2022/08/22 15:39:55 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo *philo)
{
	if (philo->right)
		free(philo);
}

void	error(t_philo *philo)
{
	free_philo(philo);
}

int	ft_atoi(const char *str)
{
	char	neg;
	size_t	i;
	size_t	value;

	neg = 1;
	i = 0;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + str[i++] - '0';
		if (value > LLONG_MAX && neg == 1)
			return (-1);
		else if (value > LLONG_MAX && neg == -1)
			return (0);
	}
	return (value * neg);
}
