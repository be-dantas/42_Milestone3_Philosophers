/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:43 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 16:20:25 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_error_mutex(char *str, t_data *data)
{
	if (data->forks)
		free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->inp.n_philo);
	if (!data->forks)
		print_error_mutex("Error malloc forks", data);
	while (i < data->inp.n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			print_error_mutex("Error init mutex", data);
		i++;
	}
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		print_error_mutex("Error init print_mutex", data);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inp.n_philo)
	{
		pthread_mutex_destroy(&data->philos[i].p_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
}
