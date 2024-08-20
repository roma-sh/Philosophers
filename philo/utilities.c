/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:11:06 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/20 18:57:30 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (nb * sign);
}

long long	get_time(void)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL))
		return (0);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_usleep(long long sleep_time, t_life *life)
{
	long long	start;
	long long	elapsed_time;

	start = get_time();
	while (1)
	{
		pthread_mutex_lock(&life->dead_lock);
		if (life->philo_dead)
		{
			pthread_mutex_unlock(&life->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&life->dead_lock);
		elapsed_time = get_time() - start;
		if (elapsed_time >= sleep_time)
			break ;

		if (sleep_time - elapsed_time > 1000)
			usleep (500);
		else
			usleep (100);
	}
}

void	print_status(t_philo *ph, char *status)
{
	long long	time;

	pthread_mutex_lock(&ph->life_cycle->print_lock);
	pthread_mutex_lock(&ph->life_cycle->dead_lock);
	time = get_time() - ph->life_cycle->big_bang;
	if (!ph->life_cycle->philo_dead)
		printf("%lld %d %s\n", time, ph->id, status);
	pthread_mutex_unlock(&ph->life_cycle->print_lock);
	pthread_mutex_unlock(&ph->life_cycle->dead_lock);
}

void	one_philo(t_life *life, int *flag)
{
	life->big_bang = get_time();
	if (life->philos_num == 1)
	{
		printf("%lld %d has taken a fork\n", get_time() - life->big_bang, 1);
		ft_usleep(life->time_to_die, life);
		printf("%lld %d died\n", get_time() - life->big_bang, 1);
		cleanup_mutexes(life, life->philos_num, flag);
		valhalla(life);
		exit(0);
	}
}
