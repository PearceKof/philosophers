/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:22:19 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/10 19:51:16 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char *s, char *color)
{
	pthread_mutex_lock(&philo->table->write_lock);
	if (is_ended(philo->table))
	{
		pthread_mutex_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%s[%ld] %d %s%s\n", color, ft_timestamp(philo), philo->id, s, NC);
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

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long int	ft_timestamp(t_philo *philo)
{
	long int	timestamp;

	timestamp = get_time() - philo->table->start_dinner_time;
	return (timestamp);
}
int	is_ended(t_table *table)
{
	int i;

	i = 0;
	pthread_mutex_lock(&table->end_lock);
	if (table->end == 1)
		i = 1;
	pthread_mutex_unlock(&table->end_lock);
	return (i);
}
void	ft_usleep(t_table *table, time_t time)
{
	time_t	end_time;

	end_time = get_time() + time;
	while (get_time() < end_time)
	{
		if (is_ended(table))
			break ;
		usleep(1);
	}
}