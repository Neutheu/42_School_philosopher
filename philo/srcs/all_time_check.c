/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_time_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:03:32 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/29 14:34:37 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*all_time_check(void *arg)
{
	t_main_struct	*main_struct;
	int				i;

	usleep(500);
	i = 0;
	main_struct = (t_main_struct*)arg;
	while (1)
	{
		while (i < main_struct->params.nb_philos)
		{
			if (check_time_to_die(&main_struct->philos[i]))
			{
				writing_death(&main_struct->philos[i], \
				get_current_time() - main_struct->starting_time, "died");
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}
