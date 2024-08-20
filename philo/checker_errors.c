/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:32:30 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 01:16:16 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	if (ft_atoi(av[1]) < 1)
	{
		printf("Error: wrong number of philosophers\n");
		return (1);
	}
	if (ft_atoi(av[2]) < 60)
	{
		printf("Error: wrong time to die\n");
		return (1);
	}
	if (ft_atoi(av[3]) < 60)
	{
		printf("Error: wrong time to eat\n");
		return (1);
	}
	if (check_args2(ac, av))
		return (1);
	return (0);
}

int	check_args2(int ac, char **av)
{
	if (ft_atoi(av[4]) < 60)
	{
		printf("Error: wrong time to sleep\n");
		return (1);
	}
	if (ac == 6 && ft_atoi(av[5]) < 1)
	{
		printf("Error: wrong number of times each philosopher must eat\n");
		return (1);
	}
	return (0);
}

void	valhalla(t_life *life)
{
	free(life->philo);
	free(life);
}
