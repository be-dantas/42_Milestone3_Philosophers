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

void	print_error_mutex(char *str, t_data *data)
{
	if (data->forks)
		free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	print_error_philo(char *str, t_data *data)
{
	if (data->philos)
		free(data->philos);
	free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	print_error_monitor(char *str, t_data *data)
{
	if (data->m)
		free(data->m);
	free(data->philos);
	free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}
