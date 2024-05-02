/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 15:25:33 by nsouchal         ###   ########.fr       */
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
			eating_even(philo);
			sleeping(philo);
		}
		else
		{
			eating_even(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

void	eating_even(t_philo *philo)
{
	while (!philo->l_fork_taken || !philo->r_fork_taken)
	{
		if (!philo->r_fork_taken)
		{
			usleep(10);
			if (check_fork(philo, 1))
			{
				set_forks_state(philo, 0, 1);
				philo->r_fork_taken = true;
				writing(philo, "has taken a fork");
			}
		}
		if (!philo->l_fork_taken)
		{
			usleep(10);
			if (check_fork(philo, 0))
			{
				set_forks_state(philo, 0, 0);
				philo->l_fork_taken = true;
				writing(philo, "has taken a fork");
			}
		}
	}
	set_time_last_meal(philo);
	writing(philo, "is eating");
	ft_usleep(philo->main_struct->params.time_to_eat);
	set_nb_meal(philo);
	set_forks_state(philo, 1, 0);
	set_forks_state(philo, 1, 1);
	philo->l_fork_taken = false;
	philo->r_fork_taken = false;
}

void	eating_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	writing(philo, "has taken a fork");
	if (philo->main_struct->params.nb_philos == 1)
	{
		ft_usleep(philo->main_struct->params.time_to_die);
		writing_death(philo, "died");
		pthread_mutex_unlock(philo->right_fork_mutex);
		return ;
	}
	pthread_mutex_lock(philo->left_fork_mutex);
	writing(philo, "has taken a fork");
	set_time_last_meal(philo);
	writing(philo, "is eating");
	ft_usleep(philo->main_struct->params.time_to_eat);
	set_nb_meal(philo);
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}

void	thinking(t_philo *philo)
{
	writing(philo, "is thinking");
	usleep(500);
}

void	sleeping(t_philo *philo)
{
	writing(philo, "is sleeping");
	ft_usleep(philo->main_struct->params.time_to_sleep);
}

