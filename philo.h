/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 17:18:40 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_input
{
	long	n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	n_eat;
}	t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	p_lock;
	long			count_eat;
	long			time_finish_eat;
	t_data			*data;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_data			*data;
}	t_monitor;

typedef struct s_data
{
	t_input			inp;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	long			start_time;
	int				flag_died;
	pthread_mutex_t	lock_flag_died;
	t_monitor		*m;
}	t_data;

//input.c
void	valid_init_input(int argc, char **argv, t_data *data);

//main.c
long	time_now(void);

//monitor.c
void	init_create_monitor(t_data *data);

//mutex.c
void	init_mutex(t_data *data);
void	destroy_mutex(t_data *data);

//philos.c
void	init_create_philo(t_data *data, int i);

//print_error.c
void	print_error_mutex(char *str, t_data *data);
void	print_error_philo(char *str, t_data *data);
void	print_error_monitor(char *str, t_data *data);

#endif
