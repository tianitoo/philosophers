/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:54:25 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:40:41 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_philo_full(t_philo *philo)
{
	t_philo	*tmp;
	int		full_philo_count;
	int		philos_count;
	int		eat_count;

	pthread_mutex_lock(philo->eat_count_mutex);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(philo->eat_count_mutex);
	tmp = philo;
	philos_count = philo->philo_count;
	full_philo_count = 0;
	while (philos_count--)
	{
		if (eat_count >= tmp->must_eat_count)
			full_philo_count++;
		tmp = tmp->next;
		pthread_mutex_lock(philo->eat_count_mutex);
		eat_count = tmp->eat_count;
		pthread_mutex_unlock(philo->eat_count_mutex);
	}
	if (full_philo_count == tmp->philo_count)
		return (1);
	return (0);
}

int	check_philo_died(t_philo *philo)
{
	int	time;
	int	last_eat;

	time = get_time();
	pthread_mutex_lock(philo->last_eat_mutex);
	last_eat = philo->last_eat;
	pthread_mutex_unlock(philo->last_eat_mutex);
	if (time - last_eat >= philo->time_to_die)
	{
		pthread_mutex_lock(philo->output);
		printf("%ld %d died\n", time - philo->start_time, philo->id);
		return (1);
	}
	return (0);
}

void	*check_death_full(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_philo_died(philo))
			break ;
		if (check_all_philo_full(philo) && philo->must_eat_count != -1)
			break ;
	}
	pthread_mutex_lock(philo->stop_mutex);
	philo->mute->stop = 1;
	pthread_mutex_unlock(philo->stop_mutex);
	ft_usleep(philo->time_to_eat + philo->time_to_sleep);
	return (NULL);
}

void	start_threading(t_philo *philo)
{
	int	i;

	i = 0;
	while (i++ < philo->philo_count && philo->must_eat_count != 0)
	{
		pthread_create(&philo->thread, NULL, philosoph, philo);
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	check_death_full(philo);
}
