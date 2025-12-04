/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:43 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 10:24:04 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->inp.n_philo);
	if (!data->forks)
		printf_exit("Error");
	while (i < data->inp.n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			printf_exit("Error");
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		printf_exit("Error");
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inp.n_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
}
