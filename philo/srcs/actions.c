/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/07 10:09:37 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_start(philo);
	philo->time_last_meal = get_current_time();
	if (philo->main_struct->param.nb_philos == 1)
		solo_philo(philo);
	if (philo->position % 2)
		usleep(10 * philo->main_struct->param.nb_philos);
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

void	eating(t_philo *philo)
{
	while (!philo->l_fork_taken || !philo->r_fork_taken)
	{
		usleep(1 * philo->main_struct->param.nb_philos);
		if (!philo->r_fork_taken)
			check_fork_and_set(philo, 1);
		if (!philo->l_fork_taken)
			check_fork_and_set(philo, 0);
	}
	writing(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->last_meal);
	ft_usleep(philo->main_struct->param.time_to_eat);
	set_and_check_nb_meal(philo);
	check_enough_meal(philo->main_struct);
	pthread_mutex_lock(philo->left_fork_mtx);
	*philo->l_fork = true;
	pthread_mutex_unlock(philo->left_fork_mtx);
	pthread_mutex_lock(philo->right_fork_mtx);
	*philo->r_fork = true;
	pthread_mutex_unlock(philo->right_fork_mtx);
	philo->l_fork_taken = false;
	philo->r_fork_taken = false;
}

void	solo_philo(t_philo *philo)
{
	writing(philo, "has taken a fork");
	ft_usleep(philo->main_struct->param.time_to_die);
	writing_death(philo);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	if (!check_dead_philo(philo->main_struct))
		printf("%zu %d %s\n", get_current_time() - \
		philo->main_struct->starting_time, philo->position, "is thinking");
	pthread_mutex_unlock(&philo->main_struct->writing);
	ft_usleep(1);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	if (!check_dead_philo(philo->main_struct))
		printf("%zu %d %s\n", get_current_time() - \
		philo->main_struct->starting_time, philo->position, "is sleeping");
	pthread_mutex_unlock(&philo->main_struct->writing);
	ft_usleep(philo->main_struct->param.time_to_sleep);
}
