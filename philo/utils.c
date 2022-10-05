/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:22:19 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/05 16:47:49 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%ld %d %s\n", ft_timestamp(philo), philo->id, s);
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

void	free_all(t_dinner *dinner)
{
	int	i;

	if (dinner)
	{
		if (dinner->philo)
		{
			i = 0;
			while (i < dinner->table->number_of_philosopher)
			{
				pthread_mutex_destroy(dinner->philo[i].l_fork);
				free(dinner->philo[i++].l_fork);
			}
			free(dinner->philo);
		}
		if (dinner->table)
			free(dinner->table);
		free(dinner);
	}
}

void	quit(char *error, t_dinner *dinner)
{
	free_all(dinner);
	if (error)
	{
		ft_putstr_fd(error, 2);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
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

void	ft_usleep(t_table *table, time_t time_in_ms)
{
	time_t	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms && table->end == 0)
		usleep(100);
}