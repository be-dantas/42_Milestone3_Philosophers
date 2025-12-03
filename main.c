/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:58:24 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 14:30:24 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
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

static int	init_philo(char **argv, t_input *inp)
{
	inp->n_philo = ft_atoi(argv[1]);
	inp->time_to_die = ft_atoi(argv[2]);
	inp->time_to_eat = ft_atoi(argv[3]);
	inp->time_to_sleep = ft_atoi(argv[4]);
	if (inp->n_philo > INT_MAX || inp->time_to_die > INT_MAX
		|| inp->time_to_eat > INT_MAX || inp->time_to_sleep > INT_MAX)
		return (0);
	return (1);
}

static void	printf_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_input	inp;

	if (argc != 5 || !valid_input(argv))
		printf_exit("Error");
	if (!init_philo(argv, &inp))
		printf_exit("Error");
}

// // Espera todos terminarem
// for (int i = 0; i < table.total_philos; i++)
//     pthread_join(philos[i].thread, NULL);

// // Destruir mutexes
// for (int i = 0; i < table.total_philos; i++)
//     pthread_mutex_destroy(&table.forks[i]);
// pthread_mutex_destroy(&table.print_lock);