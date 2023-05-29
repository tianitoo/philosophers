/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:39:38 by hnait             #+#    #+#             */
/*   Updated: 2023/05/29 20:07:34 by hnait            ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_mutex_t	output;

	philo = NULL;
	pthread_mutex_init(&output, NULL);
	if (argc < 5 || argc > 6)
		return (ft_printf("Error: wrong number of arguments\n"));
	if (check_args(argc, argv))
		return (1);
	philo = init_data(argc, argv, &output);
	if (!philo)
		return (prompt_error("Error: malloc failed"));
	start_threading(philo, ft_atoi(argv[1]));
	return (0);
}
