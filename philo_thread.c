/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:22 by hnait             #+#    #+#             */
/*   Updated: 2023/05/26 16:59:55 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_died(t_philo *philo)
{
	int	time;

	time = get_time();
	if (time - philo->last_eat > philo->time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(philo->output);
		ft_printf("%d %d died\n", time - philo->start_time, philo->id);
		ft_usleep(philo->time_to_eat + philo->time_to_sleep);
		return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	philo->last_eat = get_time();
	pthread_mutex_lock(philo->output);
	ft_printf("%d %d has taken a fork\n", philo->last_eat
		- philo->start_time, philo->id);
	ft_printf("%d %d has taken a fork\n", philo->last_eat
		- philo->start_time, philo->id);
	ft_printf("%d %d is eating\n", philo->last_eat
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
	philo->eat_count++;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	if (philo->eat_count == philo->must_eat_count)
	{
		philo->is_full = 1;
		return (1);
	}
	return (0);
}

void	*philosoph(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(300 / philo->id);
	while (!philo->is_dead && !philo->is_full)
	{
		if (eat(philo))
			break ;
		pthread_mutex_lock(philo->output);
		ft_printf("%d %d is sleeping\n", get_time()
			- philo->start_time, philo->id);
		pthread_mutex_unlock(philo->output);
		ft_usleep(philo->time_to_sleep);
		pthread_mutex_lock(philo->output);
		ft_printf("%d %d is thinking\n", get_time()
			- philo->start_time, philo->id);
		pthread_mutex_unlock(philo->output);
	}
	return (NULL);
}
