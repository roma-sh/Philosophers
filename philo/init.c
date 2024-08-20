/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:12:02 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 18:22:32 by rshatra          ###   ########.fr       */
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
	(*life)->big_bang = 0;
	(*life)->philo = NULL;
	(*life)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (*life)->philos_num);
	if (ac == 6)
		(*life)->meals_num = ft_atoi(av[5]);
	else
		(*life)->meals_num = -1;
	if (init_philos(*life))
	{
		free((*life)->forks);
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

int	init_mutexes(t_life *life)
{
	int	i;
	int	flag[6];

	i = 0;
	while (i < 6)
		flag[i++] = 0;
	i = 0;
	while (i < life->philos_num)
	{
		if (pthread_mutex_init(&(life->forks[i]), NULL) != 0)
		{
			cleanup_mutexes(life, i, flag);
			return (mutex_error(life), 1);
		}
		i++;
	}
	if (pthread_mutex_init(&(life->print_lock), NULL) != 0)
		flag[1] = 1;
	if (pthread_mutex_init(&(life->check_lock), NULL) != 0)
		flag[2] = 1;
	if (pthread_mutex_init(&(life->dead_lock), NULL) != 0)
		flag[3] = 1;
	if (keep_init(life, flag))
		return (1);
	return (0);
}

int	keep_init(t_life *life, int *flag)
{
	if (pthread_mutex_init(&(life->full_lock), NULL) != 0)
		flag[4] = 1;
	if (pthread_mutex_init(&(life->philo_ate_lock), NULL) != 0)
		flag[5] = 1;
	if (flag[1] || flag[2] || flag[3] || flag[4] || flag[5])
	{
		cleanup_mutexes(life, life->philos_num, flag);
		return (mutex_error(life), 1);
	}
	return (0);
}

void	cleanup_mutexes(t_life *life, int forks_count, int *flag)
{
	int	i;

	i = 0;
	while (i < forks_count)
	{
		pthread_mutex_destroy(&(life->forks[i]));
		i++;
	}
	if (flag[1] > 0)
		pthread_mutex_destroy(&(life->print_lock));
	if (flag[2] > 0)
		pthread_mutex_destroy(&(life->check_lock));
	if (flag[3] > 0)
		pthread_mutex_destroy(&(life->dead_lock));
	if (flag[4] > 0)
		pthread_mutex_destroy(&(life->full_lock));
	if (flag[5] > 0)
		pthread_mutex_destroy(&(life->philo_ate_lock));
}
