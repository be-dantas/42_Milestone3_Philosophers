/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 11:25:39 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while(argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '0' && !(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			if (argv[i][0] == '+')
				j++;
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static t_philo	init_philo(char **argv)
{
	t_philo	p;
	
	p.number_of_philosophers = ft_atoi(argv[1]);
	p.time_to_die = ft_atoi(argv[2]);
	p.time_to_eat = ft_atoi(argv[3]);
	p.time_to_sleep = ft_atoi(argv[4]);
}

int	main(int argc, char **argv)
{
	t_philo	p;

	if (argc != 5 || !valid_input(argv))
	{
		write(2, "Error\n", 6);
		return (0);
	}
	p = init_philo(argv);

}





// // Espera todos terminarem
// for (int i = 0; i < table.total_philos; i++)
//     pthread_join(philos[i].thread, NULL);

// // Destruir mutexes
// for (int i = 0; i < table.total_philos; i++)
//     pthread_mutex_destroy(&table.forks[i]);
// pthread_mutex_destroy(&table.print_lock);