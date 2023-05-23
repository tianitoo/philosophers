/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:41:34 by hnait             #+#    #+#             */
/*   Updated: 2023/05/23 12:10:19 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_t		death;
	int				id;
	int				eat_count;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
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
int		get_time(void);
void	is_dead(t_philo *philo);
void	print_status(t_philo *philo, char *str);
void	start_eating(t_philo *philo);
void	start_thinking(t_philo *philo);
int		prompt_error(char *str);
void	ft_usleep(long sleep);
void	start_sleeping(t_philo *philo);
void	is_dead(t_philo *philo);
t_philo	*get_last_philo(t_philo *philo);
void	*philosoph(void *arg);
int	check_args(int argc, char **argv);

#endif
