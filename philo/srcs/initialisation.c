/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:42:04 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/23 15:10:18 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialisation(t_main_struct *main_struct, int argc, char **argv)
{
	memset(main_struct->params, 0, sizeof(t_params));
	if (initialize_params(main_struct->params, argv, argc))
		return (1);
	return (create_threads(main_struct));
}

void	intialize_philos(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->params->nb_philos)
	{
		main_struct->philos[i].params = main_struct->params
	}
}

int	initialize_params(t_params *params, char **argv, int argc)
{
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (params->nb_philos <= 0 || params->nb_philos > 200 || \
	params->time_to_die <= 0 || params->time_to_eat <= 0 || \
	params->time_to_sleep <= 0)
	{
		printf("Bad arguments\n");
		return (1);
	}
	if (argc == 6)
	{
		params->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (params->number_of_times_each_philosopher_must_eat < 0 || \
		(params->number_of_times_each_philosopher_must_eat == 0 && \
		ft_strncmp(argv[5], "0", 2)))
		{
			printf("Bad arguments\n");
			return (1);
		}
	}
	return (0);
}

int	create_threads(t_main_struct *main_struct)
{
	int	i;

	i = -1;
	main_struct->philos = malloc(main_struct->params->nb_philos * \
	sizeof(t_philo));
	if (!main_struct->philos)
		return (free_all(main_struct, "Malloc error"));
	while (++i < main_struct->params->nb_philos)
	{
		if (pthread_create(&main_struct->philos[i].thread, NULL, &actions, NULL))
			return (free_all(main_struct, "pthread_create problem"));
	}
	i = -1;
	while (++i < main_struct->params->nb_philos)
	{
		if (pthread_join(main_struct->philos[i].thread, NULL))
			return (free_all(main_struct, "pthread_join problem"));
	}
	return (0);
}
