/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/25 14:29:08 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*actions(void *arg)
{
	t_philo	philo;

	philo = *(t_philo*)arg;
	while (!check_all_threads_ready(philo.main_struct))
		;
	while (!check_dead_philo(philo.main_struct))
	{
		thinking(&philo);
		eating(&philo);
		sleeping(&philo);
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
	size_t	timestamp;

	pthread_mutex_lock(philo->left_fork);
	timestamp = get_timestamp(philo->main_struct);
	if (!philo->main_struct->dead_philo)
		writing(philo, timestamp, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	timestamp = get_timestamp(philo->main_struct);
	if (!philo->main_struct->dead_philo)
		writing(philo, timestamp, "has taken a fork");
	timestamp = get_timestamp(philo->main_struct);
	if (!philo->main_struct->dead_philo)
		writing(philo, timestamp, "is eating");
	usleep(philo->main_struct->params.time_to_eat * 1000);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	thinking(t_philo *philo)
{
	size_t	timestamp;

	timestamp = get_timestamp(philo->main_struct);
	if (!philo->main_struct->dead_philo)
		writing(philo, timestamp, "is thinking");
}

void	sleeping(t_philo *philo)
{
	size_t	timestamp;

	timestamp = get_timestamp(philo->main_struct);
	if (!philo->main_struct->dead_philo)
		writing(philo, timestamp, "is sleeping");
	usleep(philo->main_struct->params.time_to_sleep * 1000);
}
