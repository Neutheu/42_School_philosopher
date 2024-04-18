/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:20:21 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/18 13:59:35 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_params		params;
	pthread_t		*philos;

	philos = NULL;
	memset(&params, 0, sizeof(t_params));
	initialize_params(&params, argv, argc);
	create_threads(philos, &params);
	if (argc != 5 && argc != 6)
	{
		printf("Bad parameters entered\n");
		return (1);
	}
	return (0);
}
