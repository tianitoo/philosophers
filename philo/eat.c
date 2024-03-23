/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:04:51 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:39:45 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_last_eat(t_philo *philo)
{
	int	last_eat;

	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat = get_time();
	last_eat = philo->last_eat;
	pthread_mutex_unlock(philo->last_eat_mutex);
	return (last_eat);
}

void	increment_eat_count(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_count_mutex);
}

void	print_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->output);
	printf("%ld %d has taken a fork\n", get_time()
		- philo->start_time, philo->id);
	printf("%ld %d has taken a fork\n", get_time()
		- philo->start_time, philo->id);
	printf("%ld %d is eating\n", get_time()
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
}

int	eat(t_philo *philo)
{
	int	eat_count;
	int	last_eat;
	int	stop;

	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->next->fork);
	last_eat = get_last_eat(philo);
	print_eating(philo);
	increment_eat_count(philo);
	eat_count = philo->eat_count;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	stop = stop_thread(philo);
	return (eat_count == philo->must_eat_count || stop);
}
