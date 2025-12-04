/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 16:22:47 by bedantas         ###   ########.fr       */
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
}	t_input;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time; /////// tirar?
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_input			inp;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long			start_time;
	int				flag_died;
}	t_data;

//input.c
void	valid_input(int argc, char **argv);
void	init_input(char **argv, t_data *data);

//main.c
void	printf_exit(char *str);
long	time_now(t_data *data);

//mutex.c
void	init_mutex(t_data *data);
void	destroy_mutex(t_data *data);

//routine.c
void	*philo_routine(void *arg);

//threads.c
void	init_philo(t_data *data);
void	create_threads(t_data *data);
void	join_threads(t_data *data);

#endif
