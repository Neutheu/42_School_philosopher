/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsouchal <nsouchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:02:23 by nsouchal          #+#    #+#             */
/*   Updated: 2024/05/02 15:20:42 by nsouchal         ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_main_struct	t_main_struct;

typedef struct s_params
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_params;

typedef struct s_philo
{
	pthread_t		thread;
	int				position;
	int				nb_meal;
	bool			*l_fork;
	bool			*r_fork;
	bool			r_fork_taken;
	bool			l_fork_taken;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	nb_meal_mutex;
	t_main_struct	*main_struct;
	size_t			time_last_meal;
}	t_philo;

typedef struct s_main_struct
{
	t_params		params;
	pthread_t		all_time_check;
	t_philo			*philos;
	pthread_mutex_t	*forks_mutex;
	bool			*forks;
	pthread_mutex_t	threads_ready;
	pthread_mutex_t	dead_philo_flag;
	pthread_mutex_t	writing;
	size_t			starting_time;
	int				all_threads_created;
	int				dead_philo;
}	t_main_struct;

int		ft_atoi(const char *nptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		initialisation(t_main_struct *main_struct, int argc, char **argv);
int		initialize_params(t_params	*params, char **argv, int argc);
int		initialize_philos(t_main_struct *main_struct);
int		initialize_mutex(t_main_struct *main_struct);
int		threads(t_main_struct *main_struct);
void	*actions(void *arg);
void	writing(t_philo *philo, char *message);
void	writing_death(t_philo *philo, char *message);
void	eating_odd(t_philo *philo);
void	eating_even(t_philo *philo);
void	thinking(t_philo *philo);
void	sleeping(t_philo *philo);
int		free_all(t_main_struct *main_struct, char *message);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);
int		destroy_mutex(t_main_struct *main_struct);
int		check_all_threads_ready(t_main_struct *main_struct);
int		check_dead_philo(t_main_struct *main_struct);
int		check_time_to_die(t_philo *philo);
void	check_must_eat(t_main_struct *main_struct);
int		check_fork(t_philo *philo, int right_or_left);
void	set_philo_died(t_main_struct *main_struct);
void	*all_time_check(void *arg);
void	set_time_last_meal(t_philo *philo);
void	set_all_threads_ready(t_main_struct *main_struct);
void	set_nb_meal(t_philo *philo);
void	set_forks_state(t_philo *philo, int true_or_false, int right_or_left);
#endif
