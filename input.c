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

static long	ft_atoi(const char *string)
{
	int		i;
	int		sign;
	long	nb;

	nb = 0;
	i = 0;
	sign = 1;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		i++;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			sign = -1;
		else if (string[i] == '+')
			sign = 1;
		if (string[i++] < '0' && string[i] > '9')
			return (0);
	}
	while (string[i] >= '0' && string[i] <= '9')
	{
		nb = nb * 10 + (string[i] - 48);
		i++;
	}
	return (sign * nb);
}

static void	valid_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5)
		printf_exit("Error input");
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][0] == '0' && !(argv[i][j] >= '0' && argv[i][j] <= '9'))
				printf_exit("Error input");
			if (argv[i][0] == '+')
				j++;
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				printf_exit("Error input");
			j++;
		}
		i++;
	}
}

void	valid_init_input(int argc, char **argv, t_data *data)
{
	valid_input(argc, argv);
	data->inp.n_philo = ft_atoi(argv[1]);
	data->inp.time_to_die = ft_atoi(argv[2]);
	data->inp.time_to_eat = ft_atoi(argv[3]);
	data->inp.time_to_sleep = ft_atoi(argv[4]);
	if (data->inp.n_philo > INT_MAX || data->inp.time_to_die > INT_MAX
		|| data->inp.time_to_eat > INT_MAX || data->inp.time_to_sleep > INT_MAX)
		printf_exit("Error INT_MAX");
}
