/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:58:43 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/04 17:43:33 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_died(t_monitor *m, int i, long t_now)
{
	pthread_mutex_lock(&m->data->print_lock);
	printf("%ld %d died\n", t_now - m->data->start_time,
		m->data->philos[i].id);
	m->data->flag_died = 1;
	pthread_mutex_unlock(&m->data->print_lock);
}

static void	*monitor(void *arg)
{
	int			i;
	long		t_now;
	long		t_die;
	t_monitor	*m;

	m = arg;
	while (m->data->flag_died != 1)
	{
		i = 0;
		while (i < m->data->inp.n_philo)
		{
			t_now = time_now();
			pthread_mutex_lock(&m->data->philos[i].p_lock);
			t_die = t_now - m->data->philos[i].time_finish_eat;
			pthread_mutex_unlock(&m->data->philos[i].p_lock);
			if (t_die > m->data->inp.time_to_die)
			{
				print_died(m, i, t_now);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static void	print_error_monitor(char *str, t_data *data)
{
	if (data->m)
		free(data->m);
	free(data->philos);
	free(data->forks);
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	init_create_monitor(t_data *data)
{
	data->m = malloc(sizeof(t_monitor));
	if (!data->m)
		print_error_monitor("Error malloc monitor", data);
	data->m->data = data;
	if (pthread_create(&data->m->thread, NULL, monitor, data->m) != 0)
		print_error_monitor("Error create monitor", data);
}
