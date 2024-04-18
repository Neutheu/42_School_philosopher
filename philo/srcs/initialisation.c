/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:42:04 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/18 15:15:27 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_params(t_params *params, char **argv, int argc)
{
	params->nb_philos = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
}

void	create_threads(pthread_t *philos, t_params *params)
{
	int	i;

	i = 0;
	philos = malloc(params->nb_philos * sizeof(pthread_t));
	while (i < params->nb_philos)
	{
		pthread_create(&philos[i], NULL, &actions, NULL);
		i++;
	}
	i = 0;
	while (i < params->nb_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
}
