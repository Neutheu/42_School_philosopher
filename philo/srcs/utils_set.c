/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:34:16 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/14 09:26:55 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	set_and_check_nb_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->nb_meal_mutex);
	philo->nb_meal++;
	if (philo->nb_meal == philo->main_struct->\
	param.number_of_times_each_philo_must_eat)
	{
		pthread_mutex_unlock(&philo->nb_meal_mutex);
		pthread_mutex_lock(&philo->main_struct->enough_meal);
		philo->main_struct->nb_philo_enough_meal++;
		pthread_mutex_unlock(&philo->main_struct->enough_meal);
		return ;
	}
	pthread_mutex_unlock(&philo->nb_meal_mutex);
}

void	wait_to_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->thread_ready);
	pthread_mutex_unlock(&philo->thread_ready);
}
