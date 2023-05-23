/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:22 by hnait             #+#    #+#             */
/*   Updated: 2023/05/23 14:39:50 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	get_time(void)
{
	struct timeval	tp;
	int			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	return (time);
}



t_philo	*get_last_philo(t_philo *philo)
{
	while (philo->next)
		philo = philo->next;
	return (philo);
}

void	*philosoph(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// if (philo->id % 2)
	// 	ft_usleep(10);
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		philo->last_eat = get_time();
		philo->eat_count++;
		// pthread_mutex_lock(philo->output);
		// ft_printf("%d %d has taken a fork\n", philo->last_eat - philo->start_time, philo->id);
		// ft_printf("%d %d has taken a fork\n", philo->last_eat - philo->start_time, philo->id);
		// ft_printf("%d %d is eating\n", philo->last_eat - philo->start_time, philo->id);
		// pthread_mutex_unlock(philo->output);
		philo->is_eating = 1;
		ft_usleep(philo->time_to_eat);
		philo->is_eating = 0;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		// pthread_mutex_lock(philo->output);
		// ft_printf("%d %d is sleeping\n", get_time() - philo->start_time, philo->id);
		// pthread_mutex_unlock(philo->output);
		philo->is_sleeping = 1;
		ft_usleep(philo->time_to_sleep);
		philo->is_sleeping = 0;
		// pthread_mutex_lock(philo->output);
		// ft_printf("%d %d is thinking\n", get_time() - philo->start_time, philo->id);
		// pthread_mutex_unlock(philo->output);
	}
	return (NULL);
}
