/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 17:10:38 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->m->thread, NULL);
	while (i < data->inp.n_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	free(data->m);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.start_time = time_now(&d);
	valid_init_input(argc, argv, &d);
	init_mutex(&d);
	init_create_philo(&d);
	init_create_monitor(&d);
	join_threads(&d);
	destroy_mutex(&d);
}
