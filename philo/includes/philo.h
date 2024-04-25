/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:02:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/04/25 14:29:41 by nsouchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_main_struct t_main_struct;

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
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_main_struct	*main_struct;
	size_t			time_last_meal;
} t_philo;

typedef struct s_main_struct
{
	t_params		params;
	pthread_t		all_time_check;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	set_threads_ready;
	pthread_mutex_t	check_threads_ready;
	pthread_mutex_t	check_dead_philo;
	pthread_mutex_t	get_timestamp;
	pthread_mutex_t	check_time_to_die;
	pthread_mutex_t	writing;
	pthread_mutex_t	philo_died;
	int				all_threads_created;
	size_t			starting_time;
	int				dead_philo;
} t_main_struct;

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		initialisation(t_main_struct *main_struct, int argc, char **argv);
int		initialize_params(t_params	*params, char **argv, int argc);
int		initialize_philos(t_main_struct *main_struct);
int		initialize_mutex(t_main_struct *main_struct);
int		threads(t_main_struct *main_struct);
void	*actions(void *arg);
void	*all_time_check(void *arg);
void	writing(t_philo *philo, size_t timestamp, char *message);
void	eating(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
int		free_all(t_main_struct *main_struct, char *message);
size_t	get_current_time(void);
int		destroy_mutex(t_main_struct *main_struct);
int		check_all_threads_ready(t_main_struct *main_struct);
int		check_dead_philo(t_main_struct *main_struct);
size_t	get_timestamp(t_main_struct *main_struct);
int		check_time_to_die(t_philo *philo);
void	set_philo_died(t_main_struct *main_struct);
void	*all_time_check(void *arg);

#endif
