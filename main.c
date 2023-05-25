/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:39:38 by hnait             #+#    #+#             */
/*   Updated: 2023/05/25 22:08:49 by hnait            ###   ########.fr       */
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
	while (get_time() < time_to_wake_up)
	{
		usleep(400);
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
				return (ft_printf("Error: wrong argument"));
		i++;
	}
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 1)
			return (ft_printf("Error: wrong argument"));
		i++;
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (ft_printf("Error: wrong argument"));
	return (0);
}

t_philo	*init_data(int argc, char **argv,  pthread_mutex_t *output)
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
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (NULL);
		tmp->id = i + 1;
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
		if (!philo)
			philo = tmp;
		else
			get_last_philo(philo)->next = tmp;
		i++;
	}
	get_last_philo(philo)->next = philo;
	return (philo);
}



t_philo	*get_precedent_philo(t_philo *philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp->next != philo)
		tmp = tmp->next;
	return (tmp);
}

int	check_philo_died(t_philo *philo)
{
	int time;

	time = get_time();
	if (time - philo->last_eat > philo->time_to_die)
	{
		philo->is_dead = 1;
		pthread_mutex_lock(philo->output);
		ft_usleep(10);
		ft_printf("%d %d died\n", time - philo->start_time, philo->id);
		return (1);
	}
	return (0);
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
			return (NULL);
		if (check_all_philo_full(philo) && philo->must_eat_count != -1)
			return (NULL);
	}
	free_all(philo);
	return (NULL);
}



int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	output;
	// pthread_t		checker;
	int				philo_count;
	int				i;

	philo = NULL;
	pthread_mutex_init(&output, NULL);
	philo_count = ft_atoi(argv[1]);
	if (argc < 5 || argc > 6)
		return (ft_printf("Error: wrong number of arguments\n"));
	if (check_args(argc, argv))
		return (1);
	philo = init_data(argc, argv, &output);
	if (!philo)
		return (prompt_error("Error: malloc failed"));
	i = 0;
	while (i++ < philo_count && philo->must_eat_count != 0)
	{
		pthread_create(&philo->thread, NULL, philosoph, philo);
		philo = philo->next;
	}
	while (i++ < philo_count && philo->must_eat_count != 0)
	{
		pthread_detach(philo->thread);
		philo = philo->next;
	}
	check_death_full(philo);
	ft_usleep(10);
	// free_all(philo);
	return (0);
}

