/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/29 14:58:27 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (!check_all_threads_ready(philo->main_struct))
		;
	if (philo->position % 2)
		usleep(200);
	while (!check_dead_philo(philo->main_struct))
	{
		if (philo->position % 2)
		{
			thinking(philo);
			eating(philo);
			sleeping(philo);
		}
		else
		{
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

void	writing(t_philo *philo, size_t timestamp, char *message)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	printf("%zu %d %s\n", timestamp, philo->position, message);
	pthread_mutex_unlock(&philo->main_struct->writing);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"has taken a fork");
	set_time_last_meal(philo);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is eating");
	usleep(philo->main_struct->params.time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	thinking(t_philo *philo)
{
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is thinking");
}

void	sleeping(t_philo *philo)
{
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is sleeping");
	usleep(philo->main_struct->params.time_to_sleep * 1000);
}
