/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 23:39:53 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/21 04:59:12 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	start_life(t_life *life)
{
	int	i;
	int	flag[6];

	i = 0;
	while (i < 6)
		flag[i++] = 1;
	one_philo(life, flag);
	life->big_bang = get_time();
	i = 0;
	while (i < life->philos_num)
	{

		pthread_mutex_lock(&life->philo->last_eat_lock);
		life->philo[i].last_eat = get_time();
		pthread_mutex_unlock(&life->philo->last_eat_lock);
		pthread_create(&life->philo[i].thread, NULL,
			life_cycle, &life->philo[i]);
		i++;
	}
	death_checker(life);
	i = 0;
	while (i < life->philos_num)
		pthread_join(life->philo[i++].thread, NULL);
	cleanup_mutexes(life, life->philos_num, flag);
}

void	*life_cycle(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2)
	{
		print_status(ph, "is thinking");
		ft_usleep(ph->life_cycle->time_to_eat, ph->life_cycle);
	}
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
	ft_usleep(ph->life_cycle->time_to_sleep, ph->life_cycle);
}

void	eat(t_philo *ph)
{
	t_life	*life;

	life = ph->life_cycle;
	if (ph->id % 2 == 0)
	{
		pthread_mutex_lock(&life->forks[ph->left_fork]);
	print_status(ph, "has taken a fork");
		pthread_mutex_lock(&life->forks[ph->right_fork]);
	print_status(ph, "has taken a fork");

	}
	else
	{
		pthread_mutex_lock(&life->forks[ph->right_fork]);
	print_status(ph, "has taken a fork");
		pthread_mutex_lock(&life->forks[ph->left_fork]);
	print_status(ph, "has taken a fork");
	}
	print_status(ph, "is eating");


	pthread_mutex_lock(&ph->last_eat_lock);
	ph->last_eat = get_time();
	pthread_mutex_unlock(&ph->last_eat_lock);


	ft_usleep(ph->life_cycle->time_to_eat, ph->life_cycle);
	pthread_mutex_lock(&life->philo_ate_lock);
	ph->eat_count++;
	pthread_mutex_unlock(&life->philo_ate_lock);
	if (ph->id % 2 == 0)
	{
		pthread_mutex_unlock(&life->forks[ph->right_fork]);
		pthread_mutex_unlock(&life->forks[ph->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&life->forks[ph->left_fork]);
		pthread_mutex_unlock(&life->forks[ph->right_fork]);
	}
}
