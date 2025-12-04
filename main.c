/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 16:22:38 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

long	time_now(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	t_data	d;

	d.start_time = time_now(&d);
	valid_input(argc, argv);
	init_input(argv, &d);
	init_mutex(&d);
	init_philo(&d);
	create_threads(&d);
	//func para monitorar threads (faz uma nova thread nela?)
	join_threads(&d);
	destroy_mutex(&d);
}
