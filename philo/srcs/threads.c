/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:05:36 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/25 14:13:27 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	threads(t_main_struct *main_struct)
{
	int	i;

	i = -1;
	while (++i < main_struct->params.nb_philos)
	{
		if (pthread_create(&main_struct->philos[i].thread, NULL, &actions, \
		&main_struct->philos[i]))
			return (free_all(main_struct, "Philo_thread_create problem"));
	}
	if (pthread_create(&main_struct->all_time_check, NULL, &all_time_check, \
		&main_struct))
			return (free_all(main_struct, "Check_all_thread_create problem"));
	pthread_mutex_lock(&main_struct->set_threads_ready);
	main_struct->all_threads_created = 1;
	pthread_mutex_unlock(&main_struct->set_threads_ready);
	i = -1;
	while (++i < main_struct->params.nb_philos)
	{
		if (pthread_join(main_struct->philos[i].thread, NULL))
			return (free_all(main_struct, "Philo_pthread_join problem"));
	}
	if (pthread_join(main_struct->all_time_check, NULL))
			return (free_all(main_struct, "Check_all_pthread_join problem"));
	return (0);
}
