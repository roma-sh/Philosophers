/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:12:02 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/18 00:09:00 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


int	init_life(int ac, char **av, t_life **life)
{
	*life = (t_life *)malloc(sizeof(t_life));
	if (!(*life))
		return (1);
	(*life)->philos_num = ft_atoi(av[1]);
	(*life)->time_to_die = ft_atoi(av[2]);
	(*life)->time_to_eat = ft_atoi(av[3]);
	(*life)->time_to_sleep = ft_atoi(av[4]);
	(*life)->all_philos_full = 0;
	(*life)->philo_dead = 0;
	(*life)->philo = NULL;
	if (ac == 6)
		(*life)->meals_num = ft_atoi(av[5]);
	else
		(*life)->meals_num = -1;
	if (init_philos(*life))
	{
		free(*life);
		return (1);
	}
	return (0);
}

int	init_philos(t_life *life)
{
	int	i;

	i = 0;
	life->philo = (t_philo *)malloc(sizeof(t_philo) * life->philos_num);
	if (!life->philo)
		return (1);
	while (i < life->philos_num)
	{
		life->philo[i].id = i + 1;
		life->philo[i].eat_count = 0;
		life->philo[i].last_eat = get_time();
		life->philo[i].life_cycle = life;
		if (i == 0)
			life->philo[i].left_fork = life->philos_num - 1;
		else
			life->philo[i].left_fork = i - 1;
		life->philo[i].right_fork = i;
		i++;
	}
	return (0);
}
