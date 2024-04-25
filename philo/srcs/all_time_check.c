/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_time_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:03:32 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/25 14:30:31 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*all_time_check(void *arg)
{
	t_main_struct	main_struct;
	size_t			timestamp;
	int				i;

	i = 0;
	main_struct = *(t_main_struct*)arg;
	while (!check_dead_philo(&main_struct))
	{
		while (i < main_struct.params.nb_philos)
		{
			if (check_time_to_die(&main_struct.philos[i]))
			{
				timestamp = get_timestamp(&main_struct);
				writing(&main_struct.philos[i], timestamp, "died");
				set_philo_died(&main_struct);
				break ;
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
