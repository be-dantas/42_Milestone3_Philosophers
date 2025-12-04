/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 11:09:32 by bedantas         ###   ########.fr       */
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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	t_input			inp;
	t_philo			*philos;
	pthread_mutex_t	*forks;	//array circular com os mutex
	pthread_mutex_t	print_mutex;
}	t_data;

//input.c
void	valid_input(int argc, char **argv);
void	init_input(char **argv, t_data *data);

//main.c
void	printf_exit(char *str);

//mutex.c
void	init_mutex(t_data *data);
void	destroy_mutex(t_data *data);

//routine.c


//threads.c
void	create_threads(t_data *data);
void	init_philo(t_data *data);
void	join_threads(t_data *data);

#endif
