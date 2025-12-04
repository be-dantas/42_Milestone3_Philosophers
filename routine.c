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

static void print_action(t_philo *p, char *str)
{
	long	t_now;
	long	time;
	
	pthread_mutex_lock(&p->data->print_lock);
	if (p->data->flag_died != 1)
	{
		t_now = time_now(&p->data);
		time = t_now - p->data->start_time;
		printf("%lld %d %s\n", time, p->id, str);
	}
	pthread_mutex_unlock(&p->data->print_lock);
	
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->id % 2 != 0)
		usleep(1000);
	while (p->data->flag_died != 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_action(p, "has taken a fork");
		
		if (p->data->inp.n_philo == 1)
		{
			usleep(p->data->inp.time_to_die * 1000);
			break ;
		}
		
		pthread_mutex_lock(p->right_fork);
		print_action(p, "has taken a fork");
		
		print_action(p, "is eating");
		usleep(p->data->inp.time_to_eat * 1000);
		p->time_finish_eat = time_now(&p->data);
		
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		
		print_action(p, "is sleeping");
		usleep(p->data->inp.time_to_sleep * 1000);
		
		print_action(p, "is thinking");
	}
}

// void	monitor(t_data *data)
// {
// 	long	t_now;

// 	while (data->flag_died != 1)
// 	{
// 		t_now = time(&data);
// 		if (t_now - data->philos[i].time_finish_eat > data->inp.time_to_die)
// 		{
// 			print_action(&data->philos[i], "died");
// 			data->flag_died = 1;
// 		}
// 	}
	

// }
