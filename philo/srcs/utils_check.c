/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:09 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/30 15:00:25 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	check_fork(t_philo *philo)
{
	int
}
