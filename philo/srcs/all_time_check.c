/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_time_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:03:32 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/06 16:46:36 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*all_time_check(void *arg)
{
	t_main_struct	*main_struct;
	int				i;

	ft_usleep(5);
	i = 0;
	main_struct = (t_main_struct *)arg;
	if (main_struct->param.nb_philos != 1)
	{
		while (!check_dead_philo(main_struct))
		{
			ft_usleep(8);
			while (i < main_struct->param.nb_philos)
			{
				if (check_time_to_die(&main_struct->philos[i]))
				{
					writing_death(&main_struct->philos[i]);
					return (NULL);
				}
				i++;
			}
			i = 0;
		}
	}
	return (NULL);
}
