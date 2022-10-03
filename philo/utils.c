/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:22:19 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/03 13:09:40 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	ft_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
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
