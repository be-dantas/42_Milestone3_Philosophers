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
	long	t_now;
	long	time;

	pthread_mutex_lock(&p->data->print_lock);
	if (p->data->flag_died != 1)
	{
		t_now = time_now();
		time = t_now - p->data->start_time;
		printf("%ld %d %s\n", time, p->id, str);
	}
	pthread_mutex_unlock(&p->data->print_lock);
}

static int	lock_unlock(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		print_action(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
		if (p->data->inp.n_philo == 1)
		{
			usleep(p->data->inp.time_to_die * 1000);
			return (0);
		}
		pthread_mutex_lock(p->right_fork);
		print_action(p, "has taken a fork");
	}
	return (1);
}

static void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->id % 2 != 0)
		usleep(1000);
	while (p->data->flag_died != 1)
	{
		if (lock_unlock(p) == 0)
			return (NULL);
		pthread_mutex_lock(&p->p_lock);
		p->time_finish_eat = time_now();
		pthread_mutex_unlock(&p->p_lock);
		print_action(p, "is eating");
		usleep(p->data->inp.time_to_eat * 1000);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		print_action(p, "is sleeping");
		usleep(p->data->inp.time_to_sleep * 1000);
		print_action(p, "is thinking");
	}
	return (NULL);
}

static void	print_error_philo(char *str, t_data *data)
{
	if (data->philos)
		free(data->philos);
	free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	init_create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->inp.n_philo);
	if (!data->philos)
		print_error_philo("Error malloc philos", data);
	while (i < data->inp.n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->inp.n_philo];
		if (pthread_mutex_init(&data->philos[i].p_lock, NULL) != 0)
			print_error_philo("Error p_lock mutex", data);
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
