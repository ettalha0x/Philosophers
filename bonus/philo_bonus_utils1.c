/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:40:42 by nettalha          #+#    #+#             */
/*   Updated: 2023/04/14 16:02:47 by nettalha         ###   ########.fr       */
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
			sem_wait(ph->sem1);
			printf("%ld %d died\n", get_time() - ph->start_time, ph->id);
			exit(0);
		}
		sem_post(ph->sem2);
		sem_wait(ph->sem3);
		if (ph->m != 0 && ph->m > ph->nb_m + 1 && ph->nb_m != -1)
			exit(0);
		sem_post(ph->sem3);
	}
}

void	ft_init_sem(t_philo *ph)
{
	sem_unlink("/sem1");
	ph->sem1 = sem_open("/sem1", O_CREAT | O_EXCL, 0666, 1);
	sem_unlink("/sem2");
	ph->sem2 = sem_open("/sem2", O_CREAT | O_EXCL, 0666, 1);
	sem_unlink("/sem3");
	ph->sem3 = sem_open("/sem3", O_CREAT | O_EXCL, 0666, 1);
	sem_unlink("/fork");
	ph->forks = sem_open("/fork", O_CREAT | O_EXCL, 0666, ph->nb_ph);
}

void	ft_init_philo(t_philo *ph, t_info *info)
{
	long	time;

	time = get_time();
	ph->m = 0;
	ph->last_meal = time;
	ph->nb_m = info->nb_meals;
	ph->nb_ph = info->nb_ph;
	ph->start_time = time;
	ph->t_to_die = info->time_to[0];
	ph->t_to_eat = info->time_to[1];
	ph->t_to_sleep = info->time_to[2];
}

void	destroy_sem(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->sem1);
	sem_close(philo->sem2);
	sem_close(philo->sem3);
}

void	ft_free(t_philo *ph)
{
	free(ph->pid);
	free(ph);
}
