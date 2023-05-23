/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:39:38 by hnait             #+#    #+#             */
/*   Updated: 2023/05/23 12:55:58 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	prompt_error(char *str)
{
	dup2(2, 1);
	ft_printf("%s\n", str);
	return (1);
}

void	ft_usleep(long sleep)
{
	long	time_to_wake_up;

	time_to_wake_up = get_time() + sleep;
	while (get_time() < time_to_wake_up)
	{
		usleep(10000);
	}
}




int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (prompt_error("Error: wrong argument"));
		i++;
	}
	return (0);
}

t_philo	*init_data(int argc, char **argv,  pthread_mutex_t *output)
{
		t_philo	*philo;
	t_philo	*tmp;
	int		i;

	i = 0;
	philo = NULL;
	while (i < ft_atoi(argv[1]))
	{
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (NULL);
		tmp->id = i + 1;
		tmp->eat_count = 0;
		tmp->is_eating = 0;
		tmp->is_sleeping = 0;
		tmp->is_thinking = 0;
		tmp->is_dead = 0;
		tmp->is_full = 0;
		tmp->philo_count = ft_atoi(argv[1]);
		tmp->time_to_die = ft_atoi(argv[2]);
		tmp->time_to_eat = ft_atoi(argv[3]);
		tmp->time_to_sleep = ft_atoi(argv[4]);
		tmp->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
		tmp->start_time = get_time();
		tmp->last_eat = tmp->start_time;
		tmp->output = output;
		tmp->next = NULL;
		if (!philo)
			philo = tmp;
		else
			get_last_philo(philo)->next = tmp;
		i++;
	}
	get_last_philo(philo)->next = philo;
	return (philo);
}

void	*check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		
		if (philo->must_eat_count != -1
			&& philo->eat_count == philo->must_eat_count)
		{
			philo->is_full = 1;
			return (NULL);
		}
		if (get_time() - philo->last_eat > philo->time_to_die)
		{
			philo->is_dead = 1;
			pthread_mutex_lock(philo->output);
			ft_printf("%d %d died\n", get_time() - philo->start_time, philo->id);
			return (NULL);
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	output;
	int				i;

	i = 0;
	philo = NULL;
	pthread_mutex_init(&output, NULL);
	if (argc < 5 || argc > 6)
		return (prompt_error("Error: wrong number of arguments"));
	if (check_args(argc, argv))
		return (1);
	philo = init_data(argc, argv, &output);
	if (!philo)
		return (prompt_error("Error: malloc failed"));
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&philo->thread, NULL, philosoph, philo);
		pthread_create(&philo->death, NULL, check_death, philo);
		i++;
		philo = philo->next;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_detach(philo->thread);
		pthread_detach(philo->death);
		i++;
		philo = philo->next;
	}
	while (1)
	{
		if (philo->is_dead || philo->is_full)
			break ;
		philo = philo->next;
	}
	free(philo);
	return (0);
}

