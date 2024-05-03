/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:34:16 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/03 12:02:35 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_all_threads_ready(t_main_struct *main_struct)
{
	pthread_mutex_lock(&main_struct->threads_ready);
	main_struct->all_threads_created = 1;
	pthread_mutex_unlock(&main_struct->threads_ready);
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

void	set_nb_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->nb_meal_mutex);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->nb_meal_mutex);
}

void	set_forks_state(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mtx);
	*philo->l_fork = true;
	pthread_mutex_unlock(philo->left_fork_mtx);
	pthread_mutex_lock(philo->right_fork_mtx);
	*philo->r_fork = true;
	pthread_mutex_unlock(philo->right_fork_mtx);
}
