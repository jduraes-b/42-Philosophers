/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:51:24 by jduraes-          #+#    #+#             */
/*   Updated: 2024/06/28 17:54:43 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

void	error(char *str, t_table *table)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	clean_table(table);
	exit(1);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	char	*str;
	size_t	i;

	i = 0;
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	str = p;
	while (i < nmemb * size)
		str[i++] = '\0';
	return (p);
}

int	philo_atoi(char *s)
{
	int			i;
	long long	r;

	i = 0;
	r = 0;
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + (s[i++] - '0');
	if (s[i] != '\0' || r > 2147483647)
		return (-1);
	return ((int)r);
}
