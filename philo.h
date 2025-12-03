/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 20:00:51 by bedantas         ###   ########.fr       */
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

typedef struct s_input
{
	long	n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_input;

typedef struct s_philo
{
	int			id;			//qual filosofo
	int			left_fork;
	int			right_fork;
	pthread_t	thread;		//qual thread esse filosofo esta
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	t_input			inp;
	t_philo			*philos;
	pthread_mutex_t	*forks;	//array circular com os mutex
	pthread_mutex_t	print_mutex;	//para nao sobrepor prints
}	t_data;

//mutex.c
void	init_mutex(t_data *data);
void	destroy_mutex(t_data *data);

//threads.c
void	create_threads(t_data *data);
void	join_threads(t_data *data);

//utils.c
void	valid_input(int argc, char **argv);
void	printf_exit(char *str);
long	ft_atoi(const char *string);

#endif
