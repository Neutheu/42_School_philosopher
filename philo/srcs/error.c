/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:15:38 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 14:47:29 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_all(t_main_struct *main_struct, char *message)
{
	if (message)
		printf("%s\n", message);
	if (main_struct->philos)
		free(main_struct->philos);
	if (main_struct->forks_mutex)
		free(main_struct->forks_mutex);
	if (main_struct->forks)
		free(main_struct->forks);
	return (1);
}
