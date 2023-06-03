/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:54:25 by hnait             #+#    #+#             */
/*   Updated: 2023/06/03 20:14:32 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_philo_full(t_philo *philo)
{
	t_philo	*tmp;
	int		eat_count;
	int		philos_count;

	tmp = philo;
	philos_count = philo->philo_count;
	eat_count = 0;
	while (philos_count--)
	{
		if (tmp->eat_count >= tmp->must_eat_count)
			eat_count++;
		tmp = tmp->next;
	}
	if (eat_count == tmp->philo_count)
	{
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
	free_all(philo);
	return (NULL);
}

void	start_threading(t_philo *philo, int philo_count)
{
	int			i;
	pthread_t	checker;

	i = 0;
	while (i++ < philo_count && philo->must_eat_count != 0)
	{
		pthread_create(&philo->thread, NULL, philosoph, philo);
		philo = philo->next;
	}
	i = 0;
	pthread_create(&checker, NULL, check_death_full, philo);
	pthread_join(checker, NULL);
	while (i++ < philo_count && philo->must_eat_count != 0)
	{
		pthread_detach(philo->thread);
		philo = philo->next;
	}
}

void	free_all(t_philo *philo)
{
	t_philo	*tmp;
	t_philo	*tmp2;

	tmp = philo;
	while (tmp->next != philo)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		pthread_mutex_destroy(&tmp2->fork);
	}
	free(tmp);
	pthread_mutex_destroy(&tmp->fork);
	pthread_mutex_destroy(tmp->output);
}
