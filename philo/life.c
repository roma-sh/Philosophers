/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:39:53 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 01:17:43 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	start_life(t_life *life)
{
	int	i;

	i = 0;
	one_philo(life);
	life->big_bang = get_time();
	while (i < life->philos_num)
	{
		pthread_create(&life->philo[i].thread, NULL,
			life_cycle, &life->philo[i]);
		i++;
	}
	i = 0;
	while (i < life->philos_num)
	{
		pthread_join(life->philo[i].thread, NULL);
		i++;
	}
	valhalla(life);
}

void	*life_cycle(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1)
	{
		if (eyes_of_the_world(ph))
			break ;
		eat(ph);
		go_sleep(ph);
		think(ph);
	}
	return (NULL);
}

void	think(t_philo *ph)
{
	print_status(ph, "is thinking");
}

void	go_sleep(t_philo *ph)
{
	print_status(ph, "is sleeping");
	ft_usleep(ph->life_cycle->time_to_sleep);
}

void	eat(t_philo *ph)
{
	print_status(ph, "has taken a fork");
	print_status(ph, "has taken a fork");
	print_status(ph, "is eating");
	ph->last_eat = get_time();
	ph->eat_count++;
	ft_usleep(ph->life_cycle->time_to_eat);
	if (ph->eat_count == ph->life_cycle->meals_num)
		ph->life_cycle->all_philos_full++;
}
