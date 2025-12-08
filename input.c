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
	long	nb;

	nb = 0;
	i = 0;
	while ((string[i] >= 9 && string[i] <= 13) || string[i] == 32)
		i++;
	if (string[i] == '+')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		nb = nb * 10 + (string[i] - 48);
		i++;
	}
	return (nb);
}

static void	print_error_input(void)
{
	printf("Error input\n");
	exit(EXIT_FAILURE);
}

static int	is_pure_zero(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	while (s[i] == '0')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

static void	valid_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5)
		print_error_input();
	while (argv[i])
	{
		j = 0;
		if (is_pure_zero(argv[i]))
			print_error_input();
		if (argv[i][0] == '+')
			j++;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				print_error_input();
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
		print_error_input();
}
