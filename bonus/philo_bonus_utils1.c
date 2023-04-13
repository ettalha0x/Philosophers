/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:42 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/13 01:48:42 by nettalha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo_bonus.h"

void	*is_died_or_full(void *void_ph)
{
	t_philo	*ph;

	ph = (t_philo *)void_ph;
	while (1)
	{
		sem_wait(ph->sem2);
		if (get_time() - ph->last_meal >= ph->t_to_die)
		{
			print_state(*ph, "died");
			exit(0);
		}
		sem_post(ph->sem2);
		sem_wait(ph->sem3);
		if (ph->m != 0 && ph->m >= ph->nb_m && ph->nb_m != -1)
			exit(0);
		sem_post(ph->sem3);
	}
}

void	ft_init_sem(t_philo *ph, t_sem *sem)
{
	int	i;

	sem->sem1 = sem_open("/sem1", O_CREAT | O_EXCL, 0666, 1);
	sem->sem2 = sem_open("/sem2", O_CREAT | O_EXCL, 0666, 1);
	sem->sem3 = sem_open("/sem3", O_CREAT | O_EXCL, 0666, 1);
	sem->forks = sem_open("/fork", O_CREAT | O_EXCL, 0666, ph->nb_ph);
	i = 0;
	while (i < ph->nb_ph)
	{
		ph[i].sem1 = &sem->sem1;
		ph[i].sem2 = &sem->sem2;
		ph[i].sem3 = &sem->sem3;
		ph[i].right_fork = &sem->forks;
		ph[i].left_fork = &sem->forks;
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

void	destroy_sem(t_philo *philo, t_sem *sem)
{
	int	i;

	i = 0;
	while (i < philo->nb_ph)
	{
		sem_close(&sem->forks[i]);
		i++;
	}
	sem_close(sem->sem1);
	sem_close(sem->sem2);
	sem_close(sem->sem3);
}

void	ft_frre(t_philo *ph, pthread_t *th, t_sem *sem)
{
	(void)sem;
	free(th);
	free(ph);
}
