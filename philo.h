/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:41:34 by hnait             #+#    #+#             */
/*   Updated: 2023/05/29 20:25:54 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	long			last_eat;
	int				is_dead;
	int				is_full;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	pthread_mutex_t	fork;
	pthread_mutex_t	*output;
	struct s_philo	*next;
}					t_philo;

t_philo	*init_data(int argc, char **argv, pthread_mutex_t *output);
void	free_all(t_philo *philo);
int		get_time(void);
void	is_dead(t_philo *philo);
void	start_eating(t_philo *philo);
void	start_thinking(t_philo *philo);
int		ft_isdigit(int c);
int		prompt_error(char *str);
int		ft_atoi(const char *str);
void	start_sleeping(t_philo *philo);
void	is_dead(t_philo *philo);
t_philo	*get_last_philo(t_philo *philo);
void	stop_all_philo(t_philo *philo);
void	start_threading(t_philo *philo, int philo_count);
void	*philosoph(void *arg);
void	ft_usleep(int sleep);
int		check_args(int argc, char **argv);
int		check_philo_died(t_philo *philo);

#endif
