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

static void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->id % 2 != 0)
		usleep(1000);
	while (p->data->flag_died != 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
		if (p->data->inp.n_philo == 1)
		{
			usleep(p->data->inp.time_to_die * 1000);
			return ;
		}
		pthread_mutex_lock(p->right_fork);
		print_action(p, "has taken a fork");
		print_action(p, "is eating");
		usleep(p->data->inp.time_to_eat * 1000);
		p->time_finish_eat = time_now(&p->data);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		print_action(p, "is sleeping");
		usleep(p->data->inp.time_to_sleep * 1000);
		print_action(p, "is thinking");
	}
}

void	init_create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->inp.n_philo);
	if (!data->philos)
		printf_exit("Error malloc philos");
	while (i < data->inp.n_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->inp.n_philo];
		data->philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->inp.n_philo)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, philo_routine, &data->philos[i]) != 0)
			printf_exit("Error create philos");
		i++;
	}
}
