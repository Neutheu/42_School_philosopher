/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:42:04 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/25 14:23:06 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialisation(t_main_struct *main_struct, int argc, char **argv)
{
	main_struct->all_threads_created = 0;
	main_struct->dead_philo = 0;
	if (initialize_params(&main_struct->params, argv, argc))
		return (1);
	if (initialize_philos(main_struct))
		return (1);
	if (initialize_mutex(main_struct))
		return (1);
	return (0);
}

int	initialize_mutex(t_main_struct *main_struct)
{
	int	i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = NULL;
	forks = malloc(main_struct->params.nb_philos * sizeof(pthread_mutex_t));
	if (!forks)
		return (free_all(main_struct, "Malloc error"));
	main_struct->forks = forks;
	while (++i < main_struct->params.nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (free_all(main_struct, "Fork_mutex init error"));
	}
	if (pthread_mutex_init(&main_struct->writing, NULL))
		return (free_all(main_struct, "Write_mutex init error"));
	if (pthread_mutex_init(&main_struct->philo_died, NULL))
		return (free_all(main_struct, "Philo_died_mutex init error"));
	if (pthread_mutex_init(&main_struct->set_threads_ready, NULL))
		return (free_all(main_struct, "Set_threads_ready_mutex init error"));
	if (pthread_mutex_init(&main_struct->check_threads_ready, NULL))
		return (free_all(main_struct, "Check_threads_ready_mutex init error"));
	if (pthread_mutex_init(&main_struct->check_dead_philo, NULL))
		return (free_all(main_struct, "Check_dead_philo_mutex init error"));
	if (pthread_mutex_init(&main_struct->get_timestamp, NULL))
		return (free_all(main_struct, "Get_timestamp_mutex init error"));
	if (pthread_mutex_init(&main_struct->check_time_to_die, NULL))
		return (free_all(main_struct, "Check_time_to_die_mutex init error"));
	i = -1;
	while (++i < main_struct->params.nb_philos)
	{
		main_struct->philos[i].left_fork = &forks[i];
		if (i == 0)
			main_struct->philos[i].right_fork = \
			&forks[main_struct->params.nb_philos - 1];
		else
			main_struct->philos[i].right_fork = &forks[i - 1];
	}
	return (0);
}

int	initialize_philos(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	main_struct->philos = NULL;
	main_struct->philos = malloc(main_struct->params.nb_philos * \
	sizeof(t_philo));
	if (!main_struct->philos)
		return (free_all(main_struct, "Malloc error"));
	while (i < main_struct->params.nb_philos)
	{
		main_struct->philos[i].position = i + 1;
		main_struct->philos[i].main_struct = main_struct;
		main_struct->philos[i].time_last_meal = get_current_time();
		i++;
	}
	return (0);
}

int	initialize_params(t_params	*params, char **argv, int argc)
{
	memset(params, 0, sizeof(t_params));
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
