/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshatra <rshatra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:34:19 by rshatra           #+#    #+#             */
/*   Updated: 2024/08/16 23:27:33 by rshatra          ###   ########.fr       */
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
	struct s_data	*data;
}					t_philo;

typedef struct s_life
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_full;
	int				philo_dead;
	t_philo			*philo;
}					t_life;

int					ft_atoi(const char *str);
int					check_args(int ac, char **av);
int					check_args2(int ac, char **av);

#endif
