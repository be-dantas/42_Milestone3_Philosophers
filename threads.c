/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:43 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 11:07:03 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inp.n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
			printf_exit("Error create philos");
		i++;
	}
}

void	init_philo(t_data *data)
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
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inp.n_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
