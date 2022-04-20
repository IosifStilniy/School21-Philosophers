/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelasafe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:48 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/20 22:21:40 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe_bonus.h"

int	timemachine(int sleeptime, struct timeval tpp[2])
{
	struct timeval	tp[2];

	if (tpp)
		return ((tpp[1].tv_sec - tpp[0].tv_sec) * 1000 + tpp[1].tv_usec / 1000 - tpp[0].tv_usec / 1000);
	gettimeofday(&tp[0], NULL);
	usleep(sleeptime * 1000 * 95 / 100);
	gettimeofday(&tp[1], NULL);
	while (timemachine(0, tp) < sleeptime)
	{
		usleep(100);
		gettimeofday(&tp[1], NULL);
	}
}

static void	what_a_wonderful_life(t_meta *meta, int id, sem_t *kushoet)
{
	struct timeval	tp;

	meta->kushoet = kushoet;
	sem_wait(meta->common->stamert);
	gettimeofday(&tp, NULL);
	meta->common->ad = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	while (1)
	{
		logger(meta, id, LOGTNK);
		sem_wait(meta->forks);
		sem_wait(meta->forks);
		sem_wait(meta->kushoet);
		logger(meta->common, id, LOGEAT);
		timemachine(meta->common->eattime, NULL);
		sem_post(meta->forks);
		sem_post(meta->forks);
		sem_post(meta->kushoet);
		logger(meta, id, LOGSLP);
		timemachine(meta->sleeptime, NULL);
	}
}

static int	checknum(char *str, char *prog)
{
	int	num;
	int	digcount;

	num = ft_atoi(str);
	if (num <= 0)
		customerrhndlr(prog, INVARGS);
	digcount = 1;
	while (num / 10 && digcount++)
		num /= 10;
	if ((int)ft_strlen(str) != digcount)
		customerrhndlr(prog, INVARGS);
	return (ft_atoi(str));
}

static int	inition(t_meta *meta, t_nkvd *nkvd, t_phela **phelas, char **argv)
{
	int		i;
	char	*prog;

	prog = *argv++;
	nkvd->numphelas = checknum(*argv++, prog);
	nkvd->lifetime = checknum(*argv++, prog);
	meta->common->eattime = checknum(*argv++, prog);
	meta->sleeptime = checknum(*argv++, prog);
	nkvd->eatcount = checknum(*argv, prog);
	nkvd->fulled = 0;
	meta->forks = sem_open("forks", O_CREAT, 420, nkvd->numphelas);
	meta->common->matyugalnik = sem_open("matyugalnik", O_CREAT, 420, 1);
	nkvd->common = meta->common;
	*phelas = malloc(sizeof(**phelas) * nkvd->numphelas);
	i = -1;
	while (++i < nkvd->numphelas)
	{
		(*phelas)->semname = ft_itoa(i + 1);
		(*phelas)->kushoet = sem_open((*phelas)->semname, O_CREAT, 420, 1);
		(*phelas)->nkvd = nkvd;
	}
	return (FALSE);
}

int	main(int argc, char **argv)
{
	t_meta		meta;
	t_nkvd		nkvd;
	t_common	common;
	t_phela		*phelas;
	int			i;

	*argv = ft_strrchr(*argv, '/') + 1;
	meta.common = &common;
	if (argc < 5 || argc > 6 || inition(&meta, &nkvd, &phelas, argv))
		customerrhndlr(*argv, INVARGS);
	common.stamert = sem_open("smert", O_CREAT, 420, 0);
	i = -1;
	while (++i < nkvd.numphelas)
	{
		phelas[i].id = i + 1;
		phelas[i].pid = fork();
		if (!phelas[i].pid)
			what_a_wonderful_life(&meta, phelas[i].id, phelas[i].kushoet);
	}
	nkvd.officers = malloc(sizeof(*nkvd.officers) * nkvd.numphelas);
	i = -1;
	while (++i <= nkvd.numphelas)
		sem_post(common.stamert);
	watch(phelas, &nkvd);
	sem_close(meta.forks);
	sem_unlink("forks");
	sem_close(common.stamert);
	sem_unlink("smert");
	return (0);
}
