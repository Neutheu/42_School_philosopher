/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:20:21 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 14:45:42 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_main_struct	main_struct;

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
