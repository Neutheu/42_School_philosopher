/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_time_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:03:32 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 15:18:15 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*all_time_check(void *arg)
{
	t_main_struct	*main_struct;
	int				i;

	ft_usleep(2);
	i = 0;
	main_struct = (t_main_struct *)arg;
	if (main_struct->params.nb_philos != 1)
	{
		while (!check_dead_philo(main_struct))
		{
			check_must_eat(main_struct);
			while (i < main_struct->params.nb_philos)
			{
				if (check_time_to_die(&main_struct->philos[i]))
				{
					writing_death(&main_struct->philos[i], "died");
					return (NULL);
				}
				i++;
			}
			i = 0;
		}
	}
	return (NULL);
}

void	check_must_eat(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	if (main_struct->params.number_of_times_each_philosopher_must_eat != -1)
	{
		while (i < main_struct->params.nb_philos)
		{
			usleep(10);
			pthread_mutex_lock(&main_struct->philos[i].nb_meal_mutex);
			if (main_struct->params.number_of_times_each_philosopher_must_eat > \
			main_struct->philos[i].nb_meal)
			{
				pthread_mutex_unlock(&main_struct->philos[i].nb_meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&main_struct->philos[i].nb_meal_mutex);
			i++;
		}
		set_philo_died(main_struct);
	}
}
