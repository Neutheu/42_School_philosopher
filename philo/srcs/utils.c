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
		if (pthread_mutex_destroy(&main_struct->philos[i].last_meal))
			return (free_all(main_struct, "Last_meal_mutex destroy problem"));
		i++;
	}
	if (pthread_mutex_destroy(&main_struct->writing))
		return (free_all(main_struct, "Write_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->dead_philo_flag))
		return (free_all(main_struct, "CheckDeadPhilo_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->threads_ready))
		return (free_all(main_struct, "ThreadsReady_mutex destroy problem"));
	free_all(main_struct, NULL);
	return (0);
}

int	check_all_threads_ready(t_main_struct *main_struct)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&main_struct->threads_ready);
	if (main_struct->all_threads_created)
		result = 1;
	pthread_mutex_unlock(&main_struct->threads_ready);
	return (result);
}

void	set_all_threads_ready(t_main_struct *main_struct)
{
	pthread_mutex_lock(&main_struct->threads_ready);
	main_struct->all_threads_created = 1;
	pthread_mutex_unlock(&main_struct->threads_ready);
}

int	check_dead_philo(t_main_struct *main_struct)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&main_struct->dead_philo_flag);
	if (main_struct->dead_philo)
		result = 1;
	pthread_mutex_unlock(&main_struct->dead_philo_flag);
	return (result);
}

int	check_time_to_die(t_philo *philo)
{
	int	result;

	result = 0;
	usleep(50);
	pthread_mutex_lock(&philo->last_meal);
	if ((get_current_time() - philo->time_last_meal) >= \
	(size_t)philo->main_struct->params.time_to_die)
		result = 1;
	pthread_mutex_unlock(&philo->last_meal);
	return (result);
}

void	set_philo_died(t_main_struct *main_struct)
{
	pthread_mutex_lock(&main_struct->dead_philo_flag);
	main_struct->dead_philo = 1;
	pthread_mutex_unlock(&main_struct->dead_philo_flag);
}

void	set_time_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal);
}

void	writing_death(t_philo *philo, size_t timestamp, char *message)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	printf("%zu %d %s\n", timestamp, philo->position, message);
	set_philo_died(philo->main_struct);
	pthread_mutex_unlock(&philo->main_struct->writing);
}
