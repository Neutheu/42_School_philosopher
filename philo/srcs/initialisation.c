/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:42:04 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/03 12:05:46 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	initialisation(t_main_struct *main_struct, int argc, char **argv)
{
	main_struct->all_threads_created = 0;
	main_struct->dead_philo = 0;
	if (initialize_param(&main_struct->param, argv, argc))
		return (1);
	if (initialize_philos(main_struct))
		return (1);
	if (initialize_mutex(main_struct))
		return (1);
	return (0);
}

void	distribute_forks(t_main_struct *main_struct)
{
	int	i;

	i = -1;
	while (++i < main_struct->param.nb_philos)
	{
		main_struct->philos[i].left_fork_mtx = &main_struct->forks_mutex[i];
		main_struct->philos[i].l_fork = &main_struct->forks[i];
	}
	i = -1;
	while (++i < main_struct->param.nb_philos)
	{
		if (i == 0)
		{
			main_struct->philos[i].right_fork_mtx = \
			main_struct->philos[main_struct->param.nb_philos - 1].left_fork_mtx;
			main_struct->philos[i].r_fork = \
			main_struct->philos[main_struct->param.nb_philos - 1].l_fork;
		}
		else
		{
			main_struct->philos[i].right_fork_mtx = \
			main_struct->philos[i - 1].left_fork_mtx;
			main_struct->philos[i].r_fork = main_struct->philos[i - 1].l_fork;
		}
	}
}

int	initialize_mutex(t_main_struct *main_struct)
{
	int				i;

	i = -1;
	main_struct->forks_mutex = malloc(main_struct->param.nb_philos * \
	sizeof(pthread_mutex_t));
	if (!main_struct->forks_mutex)
		return (free_all(main_struct, "Malloc error"));
	main_struct->forks = malloc(main_struct->param.nb_philos * sizeof(bool));
	if (!main_struct->forks)
		return (free_all(main_struct, "Malloc error"));
	while (++i < main_struct->param.nb_philos)
	{
		if (pthread_mutex_init(&main_struct->forks_mutex[i], NULL))
			return (free_all(main_struct, "Fork_mutex init error"));
		if (pthread_mutex_init(&main_struct->philos[i].last_meal, NULL))
			return (free_all(main_struct, "Last_meal_mutex init error"));
		if (pthread_mutex_init(&main_struct->philos[i].nb_meal_mutex, NULL))
			return (free_all(main_struct, "Nb_meal_mutex init error"));
		main_struct->forks[i] = true;
	}
	if (pthread_mutex_init(&main_struct->writing, NULL))
		return (free_all(main_struct, "Write_mutex init error"));
	if (pthread_mutex_init(&main_struct->threads_ready, NULL))
		return (free_all(main_struct, "Threads_ready_mutex init error"));
	if (pthread_mutex_init(&main_struct->dead_philo_flag, NULL))
		return (free_all(main_struct, "Dead_philo_flag_mutex init error"));
	i = -1;
	while (++i < main_struct->param.nb_philos)
	{
		main_struct->philos[i].left_fork_mtx = &main_struct->forks_mutex[i];
		main_struct->philos[i].l_fork = &main_struct->forks[i];
	}
	i = -1;
	while (++i < main_struct->param.nb_philos)
	{
		if (i == 0)
		{
			main_struct->philos[i].right_fork_mtx = \
			main_struct->philos[main_struct->param.nb_philos - 1].\
			left_fork_mtx;
			main_struct->philos[i].r_fork = \
			main_struct->philos[main_struct->param.nb_philos - 1].l_fork;
		}
		else
		{
			main_struct->philos[i].right_fork_mtx = \
			main_struct->philos[i - 1].left_fork_mtx;
			main_struct->philos[i].r_fork = main_struct->philos[i - 1].l_fork;
		}
	}
	return (0);
}

int	initialize_philos(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	main_struct->philos = NULL;
	main_struct->philos = malloc(main_struct->param.nb_philos * \
	sizeof(t_philo));
	if (!main_struct->philos)
		return (free_all(main_struct, "Malloc error"));
	while (i < main_struct->param.nb_philos)
	{
		main_struct->philos[i].position = i + 1;
		main_struct->philos[i].main_struct = main_struct;
		main_struct->philos[i].nb_meal = 0;
		main_struct->philos[i].l_fork_taken = false;
		main_struct->philos[i].r_fork_taken = false;
		main_struct->philos[i].r_fork = NULL;
		main_struct->philos[i].l_fork = NULL;
		i++;
	}
	return (0);
}

int	initialize_param(t_param	*param, char **argv, int argc)
{
	memset(param, -1, sizeof(t_param));
	param->nb_philos = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (param->nb_philos <= 0 || param->nb_philos > 200 || \
	param->time_to_die <= 0 || param->time_to_eat <= 0 || \
	param->time_to_sleep <= 0)
	{
		printf("Bad arguments\n");
		return (1);
	}
	if (argc == 6)
	{
		param->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
		if (param->number_of_times_each_philosopher_must_eat < 0 || \
		(param->number_of_times_each_philosopher_must_eat == 0 && \
		ft_strncmp(argv[5], "0", 2)))
		{
			printf("Bad arguments\n");
			return (1);
		}
	}
	return (0);
}
