/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:34:19 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/18 00:09:56 by rshatra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long long		last_eat;
	pthread_t		thread;
	struct s_life	*life_cycle;
}					t_philo;

typedef struct s_life
{
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_num;
	int				all_philos_full;
	int				philo_dead;
	int				someone_dead;
	long long		big_bang;
	t_philo			*philo;
}					t_life;

int					ft_atoi(const char *str);
int					check_args(int ac, char **av);
int					check_args2(int ac, char **av);
int					init_life(int ac, char **av, t_life **life);
int					init_philos(t_life *life);
void				*life_cycle(void *philo);
long long			get_time(void);
void				valhalla(t_life *life);
void				start_life(t_life *life);


#endif
