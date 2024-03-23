/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:08 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 14:52:12 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int argc, char **argv, int id)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	if (!tmp)
		return (printf("Error: malloc\n"), NULL);
	tmp->id = id + 1;
	tmp->eat_count = 0;
	tmp->start_time = get_time();
	tmp->last_eat = tmp->start_time;
	tmp->philo_count = ft_atoi(argv[1]);
	tmp->time_to_die = ft_atoi(argv[2]);
	tmp->time_to_eat = ft_atoi(argv[3]);
	tmp->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		tmp->must_eat_count = ft_atoi(argv[5]);
	else
		tmp->must_eat_count = -1;
	tmp->next = NULL;
	return (tmp);
}

void	point_on_mutex(t_philo *philo, t_mute *mute)
{
	philo->mute = mute;
	philo->output = &mute->output;
	philo->last_eat_mutex = &mute->last_eat;
	philo->eat_count_mutex = &mute->eat_count;
	philo->stop_mutex = &mute->stop_mutex;
}

t_mute	*init_mute(void)
{
	t_mute			*mute;
	pthread_mutex_t	eat_count;
	pthread_mutex_t	last_eat;
	pthread_mutex_t	stop;
	pthread_mutex_t	output;

	if (pthread_mutex_init(&eat_count, NULL)
		|| pthread_mutex_init(&output, NULL)
		|| pthread_mutex_init(&last_eat, NULL)
		|| pthread_mutex_init(&stop, NULL))
		return (printf("Error: mutex init\n"), NULL);
	mute = malloc(sizeof(t_mute));
	if (!mute)
		return (printf("Error: malloc\n"), NULL);
	mute->output = output;
	mute->eat_count = eat_count;
	mute->last_eat = last_eat;
	mute->stop_mutex = stop;
	mute->stop = 0;
	return (mute);
}

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*philo;
	t_philo	*tmp;
	t_mute	*mute;
	int		i;

	i = 0;
	mute = init_mute();
	if (!mute)
		return (NULL);
	philo = NULL;
	while (i < ft_atoi(argv[1]))
	{
		tmp = init_philo(argc, argv, i);
		if (!tmp)
			return (free_all(philo), NULL);
		pthread_mutex_init(&tmp->fork, NULL);
		point_on_mutex(tmp, mute);
		if (!philo)
			philo = tmp;
		else
			get_last_philo(philo)->next = tmp;
		i++;
	}
	get_last_philo(philo)->next = philo;
	return (philo);
}
