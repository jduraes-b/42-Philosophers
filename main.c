/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:48:01 by jduraes-          #+#    #+#             */
/*   Updated: 2024/06/28 18:05:58 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_table *table)
{
	int	i;
	int	f;

	f = 1;
	while (1)
	{
		i = -1;
		while (++i < table->pc)
		{
			if (!alive(&table->philos[i]))
			{
				f--;
				break ;
			}
		}
		if (!f)
		{
			pthread_mutex_lock(&table->restum);
			table->ff = 1;
			pthread_mutex_unlock(&table->restum);
			break ;
		}
	}
}

void	clean_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->forkmut)
	{
		while (i < table->pc)
			pthread_mutex_destroy(&table->forkmut[i++]);
	}
	if (table->forkmut)
		free(table->forkmut);
	if (table->philos)
		free(table->philos);
	free(table);
}

int	mutexstart(t_table *table)
{
	int	i;

	i = 0;
	table->forkmut = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->pc);
	if (!table->forkmut)
		return (0);
	while (i < table->pc)
		pthread_mutex_init(&table->forkmut[i++], NULL);
	i = -1;
	table->philos = ft_calloc(table->pc, sizeof(t_philo));
	table->stime = get_time();
	if (!table->philos)
		error("malloc error", table);
	while (++i <= table->pc - 1)
	{
		table->philos[i].nr = i + 1;
		table->philos[i].le = get_time();
		table->philos[i].table = table;
		table->philos[i].hunger = table->totaleats;
	}
	return (1);
}

int	argcheck(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (0);
	table->pc = philo_atoi(argv[1]);
	table->ttd = philo_atoi(argv[2]);
	table->tte = philo_atoi(argv[3]);
	table->tts = philo_atoi(argv[4]);
	table->totaleats = -1;
	if (argc == 6)
		table->totaleats = philo_atoi(argv[5]);
	if (table->pc < 1 || table->ttd < 1 || table->tte < 1 || table->tts < 1
		|| (argc == 6 && table->totaleats < 1))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)calloc(1, sizeof(t_table));
	if (!argcheck(argc, argv, table))
		error("invalid arguments", table);
	if (!mutexstart(table))
		error("init error", table);
	start(table);
	return (0);
}
