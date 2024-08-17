/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:34:22 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/18 00:09:26 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_life	*life;

	if (check_args(ac, av))
		return (1);
	if (init_life(ac, av, &life))
		return (1);
	start_life(life);
	return (0);
}

void	*life_cycle(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	printf("Philo %d is alive\n", ph->id);
	printf("Philo ate at %lld\n", ph->last_eat);
	sleep(1);
	return (NULL);
}