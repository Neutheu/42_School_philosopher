/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:20:21 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/26 12:46:05 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_main_struct	main_struct;

	main_struct.starting_time = get_current_time();
	if (argc != 5 && argc != 6)
	{
		printf("Bad parameters entered\n");
		return (1);
	}
	if (initialisation(&main_struct, argc, argv))
		return (1);
	if (threads(&main_struct))
		return (1);
	if (destroy_mutex(&main_struct))
		return (1);
	return (0);
}
