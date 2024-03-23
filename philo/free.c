/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:40:58 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:56:16 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mute(t_mute *mute)
{
	pthread_mutex_destroy(&mute->eat_count);
	pthread_mutex_destroy(&mute->last_eat);
	pthread_mutex_destroy(&mute->output);
	pthread_mutex_destroy(&mute->stop_mutex);
	free(mute);
}

void	free_all(t_philo *philo)
{
	t_mute	*mute;
	t_philo	*tmp;
	int		i;
	int		philo_count;

	philo_count = philo->philo_count;
	mute = philo->mute;
	i = 0;
	while (i++ < philo_count && philo)
	{
		tmp = philo->next;
		pthread_mutex_destroy(&tmp->fork);
		free(philo);
		philo = tmp;
	}
	free_mute(mute);
}
