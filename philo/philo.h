/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:41:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/15 23:38:11 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include<sys/time.h>

typedef struct s_info
{
	int				time_to[3];
	int				nb_meals;
	int				nb_ph;
	pthread_mutex_t	mutex1;
	pthread_mutex_t	mutex2;
	pthread_mutex_t	mutex3;
}t_info;

typedef struct s_philo
{
	int				id;
	int				t_to_eat;
	int				t_to_sleep;
	int				t_to_die;
	long			last_meal;
	long			start_time;
	int				nb_m;
	int				m;
	int				nb_ph;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*m1;
	pthread_mutex_t	*m2;
	pthread_mutex_t	*m3;
}t_philo;

long	get_time(void);
void	ft_usleep(float time);
int		is_died_or_full(t_philo *ph, t_info *info);
int		ft_atoi(const char *str);
int		check_args(char **av);
void	init_vars(char **av, t_info *info);
void	ft_init_vars(t_philo *ph, t_info *info);
void	destroy_mutex(t_philo *philo, t_info *info, pthread_mutex_t *forks);
void	ft_free(t_philo *ph, pthread_t *th, pthread_mutex_t *forks);
void	ft_init_mutex(t_philo *ph, t_info *info, pthread_mutex_t *forks);
void	threads_create(t_philo *philos, pthread_t	*threads);
void	threads_join(t_philo *philos, pthread_t *threads);
void	threads_detach(t_philo *philos, pthread_t *threads);
void	*philos_routine(void *void_philo);
void	print_state(t_philo ph, char *state, int n);
int		is_died(t_philo *ph, int i);
#endif
