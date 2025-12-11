/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:43 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 17:11:39 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_philo *p, char *str)
{
	long	time;

	pthread_mutex_lock(&p->data->lock_flag_stop);
	if (p->data->flag_stop == 1)
	{
		pthread_mutex_unlock(&p->data->lock_flag_stop);
		return ;
	}
	pthread_mutex_unlock(&p->data->lock_flag_stop);
	time = time_now() - p->data->start_time;
	pthread_mutex_lock(&p->data->lock_print);
	printf("%ld %d %s\n", time, p->id, str);
	pthread_mutex_unlock(&p->data->lock_print);
}

static void	philo_routine_eat(t_philo *p)
{
	print_action(p, "is eating");
	pthread_mutex_lock(&p->p_lock);
	p->time_finish_eat = time_now();
	p->count_eat++;
	pthread_mutex_unlock(&p->p_lock);
	func_sleep(p->data->inp.time_to_eat);
}

static int	lock_fork(t_philo *p)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (p->left_fork < p->right_fork)
	{
		first_fork = p->left_fork;
		second_fork = p->right_fork;
	}
	else
	{
		first_fork = p->right_fork;
		second_fork = p->left_fork;
	}
	pthread_mutex_lock(first_fork);
	print_action(p, "has taken a fork");
	if (p->data->inp.n_philo == 1)
	{
		func_sleep(p->data->inp.time_to_die);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	print_action(p, "has taken a fork");
	return (1);
}

static void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->id % 2 != 0)
		func_sleep(2);
	while (1)
	{
		pthread_mutex_lock(&p->data->lock_flag_stop);
		if (p->data->flag_stop == 1)
		{
			pthread_mutex_unlock(&p->data->lock_flag_stop);
			break ;
		}
		pthread_mutex_unlock(&p->data->lock_flag_stop);
		if (lock_fork(p) == 0)
			return (NULL);
		philo_routine_eat(p);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		print_action(p, "is sleeping");
		func_sleep(p->data->inp.time_to_sleep);
		print_action(p, "is thinking");
	}
	return (NULL);
}

void	init_create_philo(t_data *data, int i)
{
	data->philos = malloc(sizeof(t_philo) * data->inp.n_philo);
	if (!data->philos)
		print_error_philo("Error malloc philos", data);
	data->start_time = time_now();
	while (i < data->inp.n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->inp.n_philo];
		if (pthread_mutex_init(&data->philos[i].p_lock, NULL) != 0)
			print_error_philo("Error p_lock mutex", data);
		data->philos[i].count_eat = 0;
		data->philos[i].time_finish_eat = data->start_time;
		data->philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->inp.n_philo)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_routine, &data->philos[i]) != 0)
			print_error_philo("Error create philos", data);
		i++;
	}
}
