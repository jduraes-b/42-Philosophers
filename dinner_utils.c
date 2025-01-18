/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:19:05 by jduraes-          #+#    #+#             */
/*   Updated: 2024/06/28 18:40:20 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	rest(t_philo *philo)
{
	long long	now;
	long long	think;

	now = get_time();
	if (!action(philo, "is sleeping"))
		return (0);
	while (get_time() < now + philo->table->tts)
		;
	if (!action(philo, "is thinking"))
		return (0);
	if (philo->table->pc % 2 == 0)
		return (1);
	think = (philo->table->ttd - philo->table->tte - philo->table->tts) / 3;
	now = get_time();
	while (get_time() < now + think)
		;
	return (1);
}

int	eat(t_philo *philo)
{
	if (!action(philo, "is eating"))
	{
		pthread_mutex_unlock(&philo->table->forkmut[philo->nr - 1]);
		pthread_mutex_unlock(&philo->table->forkmut[philo->nr
			% philo->table->pc]);
		return (0);
	}
	pthread_mutex_lock(&philo->table->restum);
	philo->le = get_time();
	if (philo->hunger > 0)
		philo->hunger--;
	pthread_mutex_unlock(&philo->table->restum);
	usleep(philo->table->tte * 1000);
	pthread_mutex_unlock(&philo->table->forkmut[philo->nr - 1]);
	pthread_mutex_unlock(&philo->table->forkmut[philo->nr % philo->table->pc]);
	return (1);
}

int	single(t_philo *philo)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&philo->table->forkmut[philo->nr - 1]);
	action(philo, "has taken a fork");
	while (i)
	{
		if (get_time() - philo->table->stime > philo->table->ttd)
			i--;
	}
	pthread_mutex_unlock(&philo->table->forkmut[philo->nr - 1]);
	return (0);
}

int	action(t_philo *philo, char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->table->restum);
	if (philo->table->ff)
	{
		pthread_mutex_unlock(&philo->table->restum);
		return (0);
	}
	time = get_time() - philo->table->stime;
	printf("%lld %d %s\n", time, philo->nr, str);
	pthread_mutex_unlock(&philo->table->restum);
	return (1);
}

int	alive(t_philo *philo)
{
	static int	fullc;

	pthread_mutex_lock(&philo->table->restum);
	if (get_time() - philo->le > philo->table->ttd)
	{
		pthread_mutex_unlock(&philo->table->restum);
		action(philo, "died");
		return (0);
	}
	else if (philo->hunger == 0)
	{
		fullc++;
		philo->hunger = -1;
		if (fullc >= philo->table->pc)
		{
			printf("%lld all philosophers are full\n", get_time()
				- philo->table->stime);
			pthread_mutex_unlock(&philo->table->restum);
			return (0);
		}
		pthread_mutex_unlock(&philo->table->restum);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->restum);
	return (1);
}
