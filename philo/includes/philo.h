/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:02:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/23 14:58:41 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_params
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
} t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				position;
	t_params		params;
	pthread_mutex_t	fork;
} t_philo;

typedef struct s_main_struct
{
	t_params	*params;
	t_philo		*philos;
} t_main_struct;

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		initialisation(t_main_struct *main_struct, int argc, char **argv);
int		initialize_params(t_params *params, char **argv, int argc);
int		create_threads(t_main_struct *main_struct);
void	*actions();
int		free_all(t_main_struct *main_struct, char *message);
size_t	get_current_time(void);

#endif
