/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 11:41:56 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/14 16:12:51 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<pthread.h>
# include <semaphore.h>
# include <signal.h>
# include<sys/time.h>

typedef struct s_philo
{
	int		id;
	int		t_to_eat;
	int		t_to_sleep;
	int		t_to_die;
	long	last_meal;
	long	start_time;
	int		nb_m;
	int		m;
	int		nb_ph;
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*sem1;
	sem_t	*sem2;
	sem_t	*sem3;
}t_philo;

typedef struct s_info
{
	int		time_to[3];
	int		nb_meals;
	int		nb_ph;
}t_info;

int		check_args(char **av);
long	get_time(void);
void	ft_usleep(float time);
void	*is_died_or_full(void *void_ph);
int		ft_atoi(const char *str);
void	ft_init_vars(char **av, t_info *info);
void	ft_init_philo(t_philo *ph, t_info *info);
void	destroy_sem(t_philo *philo);
void	ft_free(t_philo *ph, pthread_t *th, sem_t *forks);
void	ft_init_sem(t_philo *ph);
void	process_create(t_philo *philos);
void	philos_routine(t_philo *ph);
void	print_state(t_philo ph, char *state);
#endif
