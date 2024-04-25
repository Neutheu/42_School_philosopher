/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                	                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:29:24 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/24 17:47:48 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	destroy_mutex(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->params.nb_philos)
	{
		if (pthread_mutex_destroy(&main_struct->forks[i]))
			return (free_all(main_struct, "Fork_mutex destroy problem"));
		i++;
	}
	if (pthread_mutex_destroy(&main_struct->writing))
		return (free_all(main_struct, "Write_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->check_dead_philo))
		return (free_all(main_struct, "CheckDeadPhilo_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->check_threads_ready))
		return (free_all(main_struct, "CheckThreadsReady_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->check_time_to_die))
		return (free_all(main_struct, "CheckTimeToDie_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->get_timestamp))
		return (free_all(main_struct, "Get_timestamp_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->set_threads_ready))
		return (free_all(main_struct, "SetThreadsReady_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->philo_died))
		return (free_all(main_struct, "Philo_died_mutex destroy problem"));
	free_all(main_struct, NULL);
	return (0);
}

int	check_all_threads_ready(t_main_struct *main_struct)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&main_struct->check_threads_ready);
	if (main_struct->all_threads_created)
		result = 1;
	pthread_mutex_unlock(&main_struct->check_threads_ready);
	return (result);
}

int	check_dead_philo(t_main_struct *main_struct)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&main_struct->check_dead_philo);
	if (main_struct->dead_philo)
		result = 1;
	pthread_mutex_unlock(&main_struct->check_dead_philo);
	return (result);
}

size_t	get_timestamp(t_main_struct *main_struct)
{
	size_t	result;

	result = 0;
	pthread_mutex_lock(&main_struct->get_timestamp);
	result = get_current_time() - main_struct->starting_time;
	pthread_mutex_unlock(&main_struct->get_timestamp);
	return (result);
}

int	check_time_to_die(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->main_struct->check_time_to_die);
	if (get_current_time() - philo->time_last_meal > \
		(size_t)philo->main_struct->params.time_to_die)
		result = 1;
	pthread_mutex_unlock(&philo->main_struct->check_time_to_die);
	return (result);
}

void	set_philo_died(t_main_struct *main_struct)
{
	pthread_mutex_lock(&main_struct->philo_died);
	main_struct->dead_philo = 1;
	pthread_mutex_unlock(&main_struct->philo_died);
}

