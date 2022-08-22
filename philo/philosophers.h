/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:51:23 by blaurent          #+#    #+#             */
/*   Updated: 2022/08/22 15:37:16 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	struct s_philo	*right;
	struct s_philo	*left;
}	t_philo;

typedef struct s_arg
{
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nbr_eat;
}	t_arg;

t_philo	*init_philo(int ag, char **av);
int	ft_atoi(const char *str);

#endif