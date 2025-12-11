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
	pthread_mutex_lock(&m->data->lock_print);
	printf("%ld %d died\n", t_now - m->data->start_time,
		m->data->philos[i].id);
	pthread_mutex_unlock(&m->data->lock_print);
	pthread_mutex_lock(&m->data->lock_flag_stop);
	m->data->flag_stop = 1;
	pthread_mutex_unlock(&m->data->lock_flag_stop);
}

static int	check_all_eat(t_monitor *m, int i, int full)
{
	t_philo	*p;

	if (m->data->inp.n_eat == -1)
		return (0);
	while (i < m->data->inp.n_philo)
	{
		p = &m->data->philos[i];
		pthread_mutex_lock(&p->p_lock);
		if (p->count_eat >= m->data->inp.n_eat)
			full++;
		pthread_mutex_unlock(&p->p_lock);
		i++;
	}
	if (full == m->data->inp.n_philo)
	{
		pthread_mutex_lock(&m->data->lock_flag_stop);
		m->data->flag_stop = 1;
		pthread_mutex_unlock(&m->data->lock_flag_stop);
		pthread_mutex_lock(&m->data->lock_print);
		printf("All philosophers have eaten enough\n");
		pthread_mutex_unlock(&m->data->lock_print);
		return (1);
	}
	return (0);
}

static int	check_die(t_monitor *m, int i)
{
	long	t_now;
	long	t_die;

	t_now = time_now();
	pthread_mutex_lock(&m->data->philos[i].p_lock);
	t_die = t_now - m->data->philos[i].time_finish_eat;
	pthread_mutex_unlock(&m->data->philos[i].p_lock);
	if (t_die > m->data->inp.time_to_die)
	{
		print_died(m, i, t_now);
		return (1);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	int			i;
	t_monitor	*m;

	m = arg;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&m->data->lock_flag_stop);
		if (m->data->flag_stop == 1)
		{
			pthread_mutex_unlock(&m->data->lock_flag_stop);
			break ;
		}
		pthread_mutex_unlock(&m->data->lock_flag_stop);
		while (i < m->data->inp.n_philo)
		{
			if (check_die(m, i))
				return (NULL);
			i++;
		}
		if (check_all_eat(m, 0, 0))
			return (NULL);
		func_sleep(1);
	}
	return (NULL);
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
