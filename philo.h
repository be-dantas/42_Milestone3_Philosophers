/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedantas <bedantas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:59 by bedantas          #+#    #+#             */
/*   Updated: 2025/12/03 14:29:43 by bedantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_input
{
	long	n_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
}	t_input;

typedef struct s_philo
{
	int	id;
	//garfo a esquerda
	//garfo a direita
}	t_philo;

//utils.c
long	ft_atoi(const char *string);

#endif
