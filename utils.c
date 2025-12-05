/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 16:27:53 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 10:30:45 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *p, char *str)
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

void	printf_exit(t_data *data, char *str)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->m)
		free(data->m);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

long	time_now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
