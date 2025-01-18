/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:47:24 by jduraes-          #+#    #+#             */
/*   Updated: 2024/06/27 19:55:35 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				nr;
	int				hunger;
	long long		le;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				pc;
	int				ttd;
	int				tte;
	int				tts;
	int				ff;
	int				totaleats;
	int				fullphilo;
	long long		stime;
	pthread_mutex_t	*forkmut;
	pthread_mutex_t	restum;
	t_philo			*philos;
}					t_table;

void				*ft_calloc(size_t nmemb, size_t size);
int					philo_atoi(char *s);
long long			get_time(void);
void				clean_table(t_table *table);
void				monitoring(t_table *table);
int					oddfork(t_philo *philo);
int					evenfork(t_philo *philo);
int					mutexstart(t_table *table);
int					oddfork(t_philo *philo);
int					evenfork(t_philo *philo);
int					grabfork(t_philo *philo);
void				*dinner(void *phil);
int					start(t_table *table);
int					single(t_philo *philo);
int					alive(t_philo *philo);
void				error(char *str, t_table *table);
int					action(t_philo *philo, char *str);
long long			get_time(void);
int					ft_strlen(char *str);
int					eat(t_philo *philo);
int					rest(t_philo *philo);

#endif
