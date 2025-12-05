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

static void	monitor(void *arg)
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
			t_now = time_now(&m->data);
			t_die = t_now - m->data->philos[i].time_finish_eat;
			if (t_die > m->data->inp.time_to_die)
			{
				pthread_mutex_lock(&m->data->print_lock);
				printf("%ld %d died\n", t_now - m->data->start_time, m->data->philos[i].id);
				m->data->flag_died = 1;
				pthread_mutex_unlock(&m->data->print_lock);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}

void	init_create_monitor(t_data *data)
{
	data->m = malloc(sizeof(t_monitor));
	if (!data->m)
		printf_exit("Error malloc monitor");
	data->m->data = data;
	if (pthread_create(&data->m->thread, NULL, monitor, data->m) != 0)
		printf_exit("Error create monitor");
}
