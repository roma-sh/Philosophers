/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:34:22 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 17:54:41 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int ac, char **av)
{
	t_life	*life;

	if (check_args(ac, av))
		return (1);
	if (init_life(ac, av, &life))
		return (2);
	if (init_mutexes(life))
		return (3);
	start_life(life);
	valhalla(life);
	return (0);
}
