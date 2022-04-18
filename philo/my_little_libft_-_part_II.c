/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_little_libft_-_part_II.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:50 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/18 22:56:50 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe.h"

int	customerrhndlr(char *prog, char *txt)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(txt, 2);
	return (1);
}

t_bool	logger(struct timeval *tp, t_phela *phela, char *txt)
{
	pthread_mutex_lock(&phela->meta->matyugalnik);
	if (phela->meta->appocalipsis && ft_strncmp(txt, LOGDTH, -1))
		pthread_mutex_unlock(&phela->meta->matyugalnik);
	if (phela->meta->appocalipsis && ft_strncmp(txt, LOGDTH, -1))
		return (TRUE);
	gettimeofday(tp, NULL);
	ft_putnbr_fd(tp->tv_sec * 1000 + tp->tv_usec / 1000 - phela->meta->ad, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(phela->id, 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(txt, 1);
	pthread_mutex_unlock(&phela->meta->matyugalnik);
	return (TRUE);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ss1;
	const unsigned char	*ss2;

	ss1 = (const unsigned char *)s1;
	ss2 = (const unsigned char *)s2;
	i = 0;
	while (ss1[i] && ss2[i] && i < n)
	{
		if (ss1[i] - ss2[i])
			return (ss1[i] - ss2[i]);
		i++;
	}
	if (i < n)
		return (ss1[i] - ss2[i]);
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	if (n / 10)
		ft_putnbr_fd((n / 10) * (n >= 0) + (n / -10) * (n < 0), fd);
	c = -1 * (n < 0) * (n % 10) + (n % 10) * (n >= 0) + '0';
	write(fd, &c, 1);
}
