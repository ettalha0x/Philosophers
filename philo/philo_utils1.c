/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 12:14:47 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/15 23:39:51 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	is_died(t_philo *ph, int i)
{
	pthread_mutex_lock(ph[i].m2);
	if (get_time() - ph[i].last_meal >= ph[i].t_to_die)
	{
		print_state(ph[i], "died", 0);
		return (0);
	}
	pthread_mutex_unlock(ph[i].m2);
	return (1);
}

void	ft_init_mutex(t_philo *ph, t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(info->mutex1), NULL);
	pthread_mutex_init(&(info->mutex2), NULL);
	pthread_mutex_init(&(info->mutex3), NULL);
	while (i < ph->nb_ph)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < ph->nb_ph)
	{
		ph[i].m1 = &info->mutex1;
		ph[i].m2 = &info->mutex2;
		ph[i].m3 = &info->mutex3;
		ph[i].right_fork = &forks[i];
		ph[i].left_fork = &forks[(i + 1) % ph->nb_ph];
		i++;
	}
}

void	ft_init_vars(t_philo *ph, t_info *info)
{
	int		i;
	long	time;

	i = 0;
	time = get_time();
	while (i < info->nb_ph)
	{
		ph[i].id = i + 1;
		ph[i].m = 0;
		ph[i].last_meal = 0;
		ph[i].nb_m = info->nb_meals;
		ph[i].nb_ph = info->nb_ph;
		ph[i].start_time = time;
		ph[i].t_to_die = info->time_to[0];
		ph[i].t_to_eat = info->time_to[1];
		ph[i].t_to_sleep = info->time_to[2];
		i++;
	}
}

void	destroy_mutex(t_philo *philo, t_info *info, pthread_mutex_t *forks)
{
	int	i;

	pthread_mutex_destroy(&info->mutex1);
	pthread_mutex_destroy(&info->mutex2);
	pthread_mutex_destroy(&info->mutex3);
	i = 0;
	while (i < philo->nb_ph)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void	ft_free(t_philo *ph, pthread_t *th, pthread_mutex_t *forks)
{
	free(forks);
	free(th);
	free(ph);
}
