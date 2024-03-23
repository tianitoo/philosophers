/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:41:34 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:10:36 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_mute
{
	int				stop;
	pthread_mutex_t	output;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	stop_mutex;
}					t_mute;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	long			last_eat;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	t_mute			*mute;
	pthread_mutex_t	fork;
	pthread_mutex_t	*output;
	pthread_mutex_t	*eat_count_mutex;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*stop_mutex;
	struct s_philo	*next;
}					t_philo;

t_philo	*init_data(int argc, char **argv);
t_philo	*get_last_philo(t_philo *philo);
int		eat(t_philo *philo);
int		get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		stop_thread(t_philo *philo);
void	start_threading(t_philo *philo);
void	free_all(t_philo *philo);
void	*philosoph(void *arg);
void	ft_usleep(int sleep);

#endif
