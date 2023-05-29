/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:53:08 by hnait             #+#    #+#             */
/*   Updated: 2023/05/26 17:02:14 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(int argc, char **argv, int id, pthread_mutex_t *output)
{
	t_philo	*tmp;

	tmp = malloc(sizeof(t_philo));
	if (!tmp)
		return (NULL);
	tmp->id = id + 1;
	tmp->eat_count = 0;
	tmp->is_dead = 0;
	tmp->is_full = 0;
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
	tmp->output = output;
	tmp->next = NULL;
	pthread_mutex_init(&tmp->fork, NULL);
	return (tmp);
}

t_philo	*init_data(int argc, char **argv, pthread_mutex_t *output)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	if (argc == 6 || argc == 5)
	{
		if (check_args(argc, argv))
			return (NULL);
	}
	else
		return (ft_printf("Error: wrong number of arguments"), NULL);
	i = 0;
	philo = NULL;
	while (i < ft_atoi(argv[1]))
	{
		tmp = init_philo(argc, argv, i, output);
		if (!philo)
			philo = tmp;
		else
			get_last_philo(philo)->next = tmp;
		i++;
	}
	get_last_philo(philo)->next = philo;
	return (philo);
}
