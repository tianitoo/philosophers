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

void	ft_usleep(int sleep)
{
	int	time_to_wake_up;

	time_to_wake_up = get_time() + sleep;
	// pthread_mutex_lock(philo->output);
	// ft_printf("id = %d, time to wake up = %d\n", philo->id, time_to_wake_up - philo->start_time);
	// pthread_mutex_unlock(philo->output);
	while (get_time() < time_to_wake_up)
	{
		usleep(1);
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
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;

	philo_count = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		must_eat_count = ft_atoi(argv[5]);
	else
		must_eat_count = -1;
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
		tmp->start_time = get_time();
		tmp->last_eat = tmp->start_time;
		tmp->philo_count = philo_count;
		tmp->time_to_die = time_to_die;
		tmp->time_to_eat = time_to_eat;
		tmp->time_to_sleep = time_to_sleep;
		tmp->must_eat_count = must_eat_count;
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
	int is_eating;
	int is_sleeping;

	philo = (t_philo *)arg;
	is_eating = 0;
	is_sleeping = 0;
	while (1)
	{
		if (is_eating != philo->is_eating && philo->is_eating)
		{
			is_eating = 1;
			pthread_mutex_lock(philo->output);
			ft_printf("%d %d has taken a fork\n", philo->last_eat - philo->start_time, philo->id);
			ft_printf("%d %d has taken a fork\n", philo->last_eat - philo->start_time, philo->id);
			ft_printf("%d %d is eating\n", philo->last_eat - philo->start_time, philo->id);
			pthread_mutex_unlock(philo->output);
		} else if (is_eating != philo->is_eating && !philo->is_eating)
			is_eating = 0;
		if (is_sleeping != philo->is_sleeping && philo->is_sleeping)
		{
			is_sleeping = 1;
			pthread_mutex_lock(philo->output);
			ft_printf("%d %d is sleeping\n", get_time() - philo->start_time, philo->id);
			pthread_mutex_unlock(philo->output);
		} else if (is_sleeping != philo->is_sleeping && !philo->is_sleeping)
		{
			is_sleeping = 0;
			pthread_mutex_lock(philo->output);
			ft_printf("%d %d is thinking\n", get_time() - philo->start_time, philo->id);
			pthread_mutex_unlock(philo->output);
		}
		if (philo->must_eat_count != -1
			&& philo->eat_count == philo->must_eat_count)
		{
			philo->is_full = 1;
			return (NULL);
		}
		if (get_time() - philo->last_eat > philo->time_to_die)
		{
			pthread_mutex_lock(philo->output);
			ft_printf("%d %d died\n", get_time() - philo->start_time, philo->id);
			philo->is_dead = 1;
			return (NULL);
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	output;
	int				philo_count;
	int				i;

	i = 0;
	philo = NULL;
	philo_count = ft_atoi(argv[1]);
	pthread_mutex_init(&output, NULL);
	if (argc < 5 || argc > 6)
		return (prompt_error("Error: wrong number of arguments"));
	if (check_args(argc, argv))
		return (1);
	philo = init_data(argc, argv, &output);
	if (!philo)
		return (prompt_error("Error: malloc failed"));
	while (i < philo_count)
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

