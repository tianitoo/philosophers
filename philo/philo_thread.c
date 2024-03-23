/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:00:22 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:04:47 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_thread(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(philo->stop_mutex);
	stop = philo->mute->stop;
	pthread_mutex_unlock(philo->stop_mutex);
	return (stop);
}

int	sleeping(t_philo *philo)
{
	int	stop;

	pthread_mutex_lock(philo->output);
	printf("%ld %d is sleeping\n", get_time()
		- philo->start_time, philo->id);
	pthread_mutex_unlock(philo->output);
	ft_usleep(philo->time_to_sleep);
	stop = stop_thread(philo);
	return (stop);
}

void	*philosoph(void *arg)
{
	t_philo	*philo;
	int		stop;

	stop = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (!stop)
	{
		if (eat(philo))
			break ;
		if (sleeping(philo))
			break ;
		pthread_mutex_lock(philo->output);
		printf("%ld %d is thinking\n", get_time()
			- philo->start_time, philo->id);
		pthread_mutex_unlock(philo->output);
		stop = stop_thread(philo);
	}
	return (NULL);
}
