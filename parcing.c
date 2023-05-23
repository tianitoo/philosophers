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
	if (philo->id % 2)
		ft_usleep(philo->time_to_eat / 2);
	while (1)
	{
		start_eating(philo);
		start_sleeping(philo);
		start_thinking(philo);
	}
	return (NULL);
}

void	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(philo->output);
	ft_printf("%d %d has taken a fork\n", get_time()
		- philo->start_time, philo->id);
	ft_printf("%d %d has taken a fork\n", get_time()
		- philo->start_time, philo->id);
	ft_printf("%d %d is eating\n", get_time()
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
	philo->last_eat = get_time();
	philo->eat_count++;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);git 
}

void	start_sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	ft_printf("%d %d is sleeping\n", get_time()
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
	ft_usleep(philo->time_to_sleep);
}

void	start_thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	ft_printf("%d %d is thinking\n", get_time()
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
}
