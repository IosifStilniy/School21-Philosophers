/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_little_libft_-_part_II_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:50 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/22 18:51:22 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe_bonus.h"

int	customerrhndlr(char *prog, char *txt)
{
	ft_putstr_fd(prog, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(txt, 2);
	exit(1);
}

// static void	*printer(void *arg)
// {
// 	struct timeval	tp;
// 	t_log			*log;

// 	log = (t_log *)arg;
// 	if (!log->dvuhsotiy)
// 		sem_wait(log->common->matyugalnik);
// 	gettimeofday(&tp, NULL);
// 	ft_putnbr_fd(tp.tv_sec * 1000 + tp.tv_usec / 1000 - log->common->ad, 1);
// 	ft_putstr_fd(" ", 1);
// 	ft_putnbr_fd(log->id, 1);
// 	ft_putstr_fd(" ", 1);
// 	ft_putendl_fd(log->txt, 1);
// 	if (!log->dvuhsotiy)
// 		sem_post(log->common->matyugalnik);
// 	return (NULL);
// }

// void	logger(t_common *common, int id, char *txt)
// {
// 	t_log	log;

// 	log.common = common;
// 	log.id = id;
// 	log.txt = txt;
// 	log.dvuhsotiy = TRUE;
// 	if (ft_strncmp(txt, LOGDTH, -1) && log.dvuhsotiy--)
// 	{
// 		sem_wait(common->stamert);
// 		sem_post(common->stamert);
// 	}
// 	pthread_create(&log.t, NULL, &printer, &log);
// 	if (!ft_strncmp(txt, LOGDTH, -1))
// 		pthread_join(log.t, NULL);
// 	else
// 		pthread_detach(log.t);
// }

void	logger(t_common *common, int id, char *txt)
{
	struct timeval	tp;

	if (ft_strncmp(txt, LOGDTH, -1))
	{
		sem_wait(common->stamert);
		sem_post(common->stamert);
	}
	sem_wait(common->matyugalnik);
	gettimeofday(&tp, NULL);
	ft_putnbr_fd(tp.tv_sec * 1000 + tp.tv_usec / 1000 - common->ad, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(id, 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(txt, 1);
	sem_post(common->matyugalnik);
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
