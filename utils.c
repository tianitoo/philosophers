/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:51:55 by hnait             #+#    #+#             */
/*   Updated: 2023/05/26 16:56:33 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tp;
	int				time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000;
	time += tp.tv_usec / 1000;
	return (time);
}

void	ft_usleep(int sleep)
{
	int	time_to_wake_up;

	time_to_wake_up = get_time() + sleep;
	while (get_time() < time_to_wake_up)
	{
		usleep(400);
	}
}

t_philo	*get_last_philo(t_philo *philo)
{
	while (philo->next)
		philo = philo->next;
	return (philo);
}

int	prompt_error(char *str)
{
	dup2(2, 1);
	ft_printf("%s\n", str);
	return (1);
}

t_philo	*get_precedent_philo(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->next != philo)
		tmp = tmp->next;
	return (tmp);
}
