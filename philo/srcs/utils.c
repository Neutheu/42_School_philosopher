/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                	                    +:+ +:+         +:+   */
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

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	destroy_mutex(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->param.nb_philos)
	{
		if (pthread_mutex_destroy(&main_struct->forks_mutex[i]))
			return (free_all(main_struct, "Fork_mutex destroy problem"));
		if (pthread_mutex_destroy(&main_struct->philos[i].last_meal))
			return (free_all(main_struct, "Last_meal_mutex destroy problem"));
		if (pthread_mutex_destroy(&main_struct->philos[i].nb_meal_mutex))
			return (free_all(main_struct, "Nb_meal_mutex destroy problem"));
		if (pthread_mutex_destroy(&main_struct->philos[i].thread_ready))
			return (free_all(main_struct, "Thrd_ready_mutex destroy problem"));
		i++;
	}
	if (pthread_mutex_destroy(&main_struct->writing))
		return (free_all(main_struct, "Write_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->dead_philo_flag))
		return (free_all(main_struct, "CheckDeadPhilo_mutex destroy problem"));
	if (pthread_mutex_destroy(&main_struct->enough_meal))
		return (free_all(main_struct, "Enough_meal_mutex destroy problem"));
	free_all(main_struct, NULL);
	return (0);
}

void	writing_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	if (!check_dead_philo(philo->main_struct))
		printf("%zu %d died\n", get_current_time() - \
		philo->main_struct->starting_time, philo->position);
	set_philo_died(philo->main_struct);
	pthread_mutex_unlock(&philo->main_struct->writing);
}

void	writing(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->main_struct->writing);
	if (!check_dead_philo(philo->main_struct))
		printf("%zu %d %s\n", get_current_time() - \
		philo->main_struct->starting_time, philo->position, message);
	pthread_mutex_unlock(&philo->main_struct->writing);
}
