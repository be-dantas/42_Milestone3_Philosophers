/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 13:59:30 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	d;

	valid_input(argc, argv);
	init_input(argv, &d);
	init_mutex(&d);
	init_philo(&d);
	create_threads(&d);
	join_threads(&d);
	destroy_mutex(&d);
}
