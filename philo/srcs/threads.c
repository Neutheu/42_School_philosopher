/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:05:36 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 15:21:49 by nsouchal         ###   ########.fr       */
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
		main_struct))
		return (free_all(main_struct, "Check_all_thread_create problem"));
	main_struct->starting_time = get_current_time();
	set_all_threads_ready(main_struct);
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
