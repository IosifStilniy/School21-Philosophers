/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nkvd_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:33:43 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/23 15:21:23 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe_bonus.h"

int	timemachine(int sleeptime, struct timeval tpp[2])
{
	struct timeval	tp[2];

	if (tpp)
		return ((tpp[1].tv_sec - tpp[0].tv_sec) * 1000 + tpp[1].tv_usec / 1000
			- tpp[0].tv_usec / 1000);
	gettimeofday(&tp[0], NULL);
	usleep(sleeptime * 1000 * 95 / 100);
	gettimeofday(&tp[1], NULL);
	while (timemachine(0, tp) < sleeptime)
	{
		usleep(100);
		gettimeofday(&tp[1], NULL);
	}
	return (0);
}

static t_bool	morg(t_phela *phela, struct timeval tp[2], int *lastmeal,
	int *eatcount)
{
	if (timemachine(0, tp) > phela->nkvd->common->eattime * 90 / 100)
	{
		*lastmeal = 0;
		*eatcount += 1;
		if (*eatcount == phela->nkvd->eatcount)
			phela->nkvd->fulled++;
	}
	else
	{
		if (!timemachine(0, tp))
		{
			usleep(1000);
			gettimeofday(&tp[1], NULL);
		}
		*lastmeal += timemachine(0, tp);
	}
	if (*lastmeal < phela->nkvd->lifetime)
		return (FALSE);
	sem_wait(phela->nkvd->common->stamert);
	if (phela->nkvd->dvuhsotiy || phela->nkvd->fulled == phela->nkvd->numphelas)
		return (TRUE);
	logger(phela->nkvd->common, phela->id, LOGDTH);
	phela->nkvd->dvuhsotiy = TRUE;
	return (TRUE);
}

static void	jdun(sem_t *kushoet)
{
	sem_wait(kushoet);
	sem_post(kushoet);
	exit(0);
}

static void	*shift(void *arg)
{
	struct timeval	tp[2];
	t_phela			*phela;
	int				lastmeal;
	int				eatcount;

	phela = (t_phela *)arg;
	eatcount = 0;
	gettimeofday(&tp[0], NULL);
	lastmeal = tp[0].tv_sec * 1000 + tp[0].tv_usec / 1000
		- phela->nkvd->common->ad;
	while (!phela->nkvd->dvuhsotiy
		&& phela->nkvd->fulled < phela->nkvd->numphelas)
	{
		phela->omnomnom = fork();
		if (!phela->omnomnom)
			jdun(phela->kushoet);
		waitpid(phela->omnomnom, NULL, WUNTRACED);
		phela->omnomnom = 0;
		gettimeofday(&tp[1], NULL);
		if (morg(phela, tp, &lastmeal, &eatcount))
			return (NULL);
		gettimeofday(&tp[0], NULL);
	}
	return (NULL);
}

void	watch(t_phela *phelas, t_nkvd *nkvd)
{
	struct timeval	tp;
	int				i;

	gettimeofday(&tp, NULL);
	nkvd->common->ad = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	i = -1;
	while (++i < nkvd->numphelas)
		if (pthread_create(&nkvd->officers[i], NULL, &shift, &phelas[i])
			|| pthread_detach(nkvd->officers[i]))
			continue ;
	while (!nkvd->dvuhsotiy && nkvd->fulled < nkvd->numphelas)
		;
	sem_wait(nkvd->common->matyugalnik);
	i = -1;
	while (++i < nkvd->numphelas)
	{
		if (phelas[i].omnomnom)
			kill(phelas[i].omnomnom, SIGINT);
		kill(phelas[i].pid, SIGINT);
		sem_unlink(phelas[i].semname);
	}
	sem_unlink("matyugalnik");
	sem_unlink("forks");
	sem_unlink("smert");
}
