/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blaurent <blaurent@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:51:23 by blaurent          #+#    #+#             */
/*   Updated: 2022/10/19 14:35:07 by blaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>

typedef struct s_table
{
	int				nb_of_philo;
	int				to_eat;
	int				end;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			dinner_start;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	write_lock;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				nb_of_meal;
	time_t			last_meal;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_dinner
{
	t_table		*table;
	t_philo		*philo;
	pthread_t	death_checker;
}	t_dinner;

void	quit(char *error, t_dinner *dinner);

int		init_table(t_dinner *dinner, int ac, char **av);
int		init_philo(t_dinner *dinner, int nb_philo);

void	*philosopher(void *data);

void	*death_check(void *data);

time_t	get_time(void);
void	ft_usleep(t_table *table, long int time);
void	wait_start(time_t start_dinner_time);

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
void	print_state(t_philo *philo, char *s);
int		dinner_stopped(t_table *table);

#endif