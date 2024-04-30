/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/30 15:05:59 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_all_threads_ready(philo->main_struct))
		;
	if (philo->position % 2)
		usleep(100);
	while (!check_dead_philo(philo->main_struct))
	{
		if (philo->position % 2)
		{
			thinking(philo);
			eating_odd(philo);
			sleeping(philo);
		}
		else
		{
			eating_odd(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

void	eating_even(t_philo *philo)
{
	/*
		- checker premiere fourchette avec son mutex
		- checker deuxieme
		- checker tant quelles sont pas dispos
		- set les fourchette a false
		- manger
		- set les fourchettes a true
	*/
}

void	eating_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"has taken a fork");
	if (philo->main_struct->params.nb_philos == 1)
	{
		ft_usleep(philo->main_struct->params.time_to_die);
		writing_death(philo, get_current_time() - \
		philo->main_struct->starting_time, "died");
		pthread_mutex_unlock(philo->right_fork_mutex);
		return ;
	}
	pthread_mutex_lock(philo->left_fork_mutex);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"has taken a fork");
	set_time_last_meal(philo);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is eating");
	ft_usleep(philo->main_struct->params.time_to_eat);
	set_nb_meal(philo);
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}

void	thinking(t_philo *philo)
{
	ft_usleep(1);
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is thinking");
}

void	sleeping(t_philo *philo)
{
	if (!check_dead_philo(philo->main_struct))
		writing(philo, get_current_time() - philo->main_struct->starting_time, \
		"is sleeping");
	ft_usleep(philo->main_struct->params.time_to_sleep);
}

