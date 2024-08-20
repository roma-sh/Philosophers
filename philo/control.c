/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 01:27:30 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 01:28:05 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	eyes_of_the_world(t_philo *ph)
{
	long long	time;

	time = get_time();
	if (ph->life_cycle->meals_num > 0
		&& ph->eat_count >= ph->life_cycle->meals_num)
		return (1);
	if (ph->life_cycle->all_philos_full == ph->life_cycle->philos_num)
		return (1);
	if (ph->life_cycle->philo_dead)
		return (1);
	if (time - ph->last_eat > ph->life_cycle->time_to_die)
	{
		if (!ph->life_cycle->philo_dead)
		{
			ph->life_cycle->philo_dead = 1;
			print_status(ph, "died");
		}
		return (1);
	}
	return (0);
}
