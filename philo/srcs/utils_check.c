/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:33:09 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/03 12:10:57 by nsouchal         ###   ########.fr       */
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
	(size_t)philo->main_struct->param.time_to_die)
		result = 1;
	pthread_mutex_unlock(&philo->last_meal);
	return (result);
}

int	check_fork_and_set(t_philo *philo, int right_or_left)
{
	int	result;

	result = 0;
	if (!right_or_left)
	{
		pthread_mutex_lock(philo->left_fork_mtx);
		if (*philo->l_fork)
		{
			*philo->l_fork = false;
			philo->l_fork_taken = true;
			result = 1;
		}
		pthread_mutex_unlock(philo->left_fork_mtx);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mtx);
		if (*philo->r_fork)
		{
			*philo->r_fork = false;
			philo->r_fork_taken = true;
			result = 1;
		}
		pthread_mutex_unlock(philo->right_fork_mtx);
	}
	return (result);
}
