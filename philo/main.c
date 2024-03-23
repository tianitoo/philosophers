/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:39:38 by hnait             #+#    #+#             */
/*   Updated: 2023/06/08 15:51:41 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
				return (printf("Error: wrong argument"));
		i++;
	}
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 1)
			return (printf("Error: wrong argument"));
		i++;
	}
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (printf("Error: wrong argument"));
	if (argc == 6 && ft_atoi(argv[5]) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;

	philo = NULL;
	if (argc < 5 || argc > 6)
		return (printf("Error: wrong number of arguments\n"));
	if (check_args(argc, argv))
		return (0);
	philo = init_data(argc, argv);
	if (!philo)
		return (printf("Error: malloc failed"));
	start_threading(philo);
	free_all(philo);
	return (0);
}
