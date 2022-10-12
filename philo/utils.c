/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:22:19 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/12 17:41:50 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char *s, char *color)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (dinner_stopped(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%s[%ld] %d %s%s\n", color,
		get_time() - philo->table->start_dinner_time, philo->id, s, NC);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
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
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9' && value < INT_MAX)
	{
		value = (value * 10) + str[i++] - '0';
	}
	if (value > INT_MAX)
		return (-2);
	return (value * neg);
}

int	dinner_stopped(t_table *table)
{
	int i;

	i = 0;
	pthread_mutex_lock(&table->end_lock);
	if (table->end == 1)
		i = 1;
	pthread_mutex_unlock(&table->end_lock);
	return (i);
}
