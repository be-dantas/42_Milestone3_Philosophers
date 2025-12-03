/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 16:40:09 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo(char **argv, t_input *inp)
{
	inp->n_philo = ft_atoi(argv[1]);
	inp->time_to_die = ft_atoi(argv[2]);
	inp->time_to_eat = ft_atoi(argv[3]);
	inp->time_to_sleep = ft_atoi(argv[4]);
	if (inp->n_philo > INT_MAX || inp->time_to_die > INT_MAX
		|| inp->time_to_eat > INT_MAX || inp->time_to_sleep > INT_MAX)
		printf_exit("Error");
}

static void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->inp.n_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_input	inp;
	t_data	d;

	if (argc != 5 || !valid_input(argv))
		printf_exit("Error");
	init_philo(argv, &inp);
	d.inp = inp;
	init_mutex(&d); //func mutex
	//func while threads
	thread_join(&d); //func pthread_join ("waitpid")
	destroy_mutex(&d); //func destruir mutex
}
