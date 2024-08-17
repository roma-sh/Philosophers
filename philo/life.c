/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:39:53 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/18 00:10:43 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	start_life(t_life *life)
{
	int	i;

	i = 0;
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
