/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 19:41:51 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_input(char **argv, t_data *data)
{
	data->inp.n_philo = ft_atoi(argv[1]);
	data->inp.time_to_die = ft_atoi(argv[2]);
	data->inp.time_to_eat = ft_atoi(argv[3]);
	data->inp.time_to_sleep = ft_atoi(argv[4]);
	if (data->inp.n_philo > INT_MAX || data->inp.time_to_die > INT_MAX
		|| data->inp.time_to_eat > INT_MAX || data->inp.time_to_sleep > INT_MAX)
		printf_exit("Error");
}

int	main(int argc, char **argv)
{
	t_data	d;

	valid_input(argc, argv);
	init_input(argv, &d);
	init_mutex(&d); //func mutex
	create_threads(&d); //func while threads
	join_threads(&d); //func pthread_join ("waitpid")
	destroy_mutex(&d); //func destruir mutex
}
