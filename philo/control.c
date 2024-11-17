/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 01:27:30 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/21 06:07:38 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	eyes_of_the_world(t_philo *ph)
{
	pthread_mutex_lock(&ph->life_cycle->philo_ate_lock);
	if (ph->life_cycle->meals_num > 0
		&& ph->eat_count >= ph->life_cycle->meals_num)
		{
	pthread_mutex_unlock(&ph->life_cycle->philo_ate_lock);

		return (1);
		}
	pthread_mutex_unlock(&ph->life_cycle->philo_ate_lock);
	pthread_mutex_lock(&ph->life_cycle->full_lock);

	if (ph->life_cycle->all_philos_full)
	{
	pthread_mutex_unlock(&ph->life_cycle->full_lock);

		return (1);
	}
	pthread_mutex_unlock(&ph->life_cycle->full_lock);
	pthread_mutex_lock(&ph->life_cycle->dead_lock);
	if (ph->life_cycle->philo_dead)
	{
		pthread_mutex_unlock(&ph->life_cycle->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&ph->life_cycle->dead_lock);
	return (0);
}

void	death_checker(t_life *life)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&life->dead_lock);
		pthread_mutex_lock(&life->full_lock);
		if (life->philo_dead || life->all_philos_full)
		{
			pthread_mutex_unlock(&life->dead_lock);
			pthread_mutex_unlock(&life->full_lock);
			break ;
		}
		pthread_mutex_unlock(&life->dead_lock);
		pthread_mutex_unlock(&life->full_lock);
		while (life->meals_num > 0 && i < life->philos_num
			&& life->philo[i].eat_count >= life->meals_num)
			i++;
		if (i == life->philos_num)
		{
			pthread_mutex_lock(&life->full_lock);
			life->all_philos_full = 1;
			pthread_mutex_unlock(&life->full_lock);
			break ;
		}
		death_checker_2nd(life);
	}
}

void	death_checker_2nd(t_life *life)
{
	int	i;

	i = 0;
	while (i < life->philos_num)
	{
		pthread_mutex_lock(&life->dead_lock);
		if (life->philo_dead)
		{
			pthread_mutex_unlock(&life->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&life->dead_lock);
		pthread_mutex_lock(&life->philo[i].last_eat_lock);
		if (get_time() - life->philo[i].last_eat >= life->time_to_die)
		{
			print_status(&life->philo[i], "died");
			pthread_mutex_lock(&life->dead_lock);
			life->philo_dead = 1;
			pthread_mutex_unlock(&life->dead_lock);
			pthread_mutex_unlock(&life->philo[i].last_eat_lock);
			break ;
		}
		pthread_mutex_unlock(&life->philo[i++].last_eat_lock);
		usleep(100);
	}
}
