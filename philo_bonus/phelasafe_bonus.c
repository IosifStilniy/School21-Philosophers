/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phelasafe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:56:48 by dcelsa            #+#    #+#             */
/*   Updated: 2022/06/08 19:35:15 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe_bonus.h"

sem_t	*semhndlr(char *semname, int def, sem_t *out)
{
	sem_t	*sem;

	if (out)
		sem_close(out);
	sem_unlink(semname);
	if (out)
		return (NULL);
	sem = sem_open(semname, O_CREAT | O_EXCL, 420, def);
	while (sem == SEM_FAILED)
		sem = sem_open(semname, O_CREAT | O_EXCL, 420, def);
	return (sem);
}

static void	what_a_wonderful_life(t_meta *meta, int id, sem_t *kushoet)
{
	struct timeval	tp;

	sem_wait(meta->common->stamert);
	gettimeofday(&tp, NULL);
	meta->common->ad = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	while (1)
	{
		logger(meta->common, id, LOGTNK);
		sem_wait(meta->forks);
		logger(meta->common, id, LOGFRK);
		sem_wait(meta->forks);
		logger(meta->common, id, LOGFRK);
		sem_wait(kushoet);
		logger(meta->common, id, LOGEAT);
		timemachine(meta->common->eattime, NULL);
		sem_post(meta->forks);
		sem_post(meta->forks);
		sem_post(kushoet);
		logger(meta->common, id, LOGSLP);
		timemachine(meta->sleeptime, NULL);
	}
}

static int	checknum(char *str, char *prog)
{
	int	num;
	int	digcount;

	num = ft_atoi(str);
	if (str && num <= 0)
		customerrhndlr(prog, INVARGS);
	digcount = 1;
	while (num / 10 && digcount++)
		num /= 10;
	if (str && (int)ft_strlen(str) != digcount)
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
	nkvd->dvuhsotiy = FALSE;
	meta->forks = semhndlr("forks", nkvd->numphelas, NULL);
	meta->common->matyugalnik = semhndlr("matyugalnik", 1, NULL);
	nkvd->common = meta->common;
	*phelas = malloc(sizeof(**phelas) * nkvd->numphelas);
	i = -1;
	while (++i < nkvd->numphelas)
	{
		(*phelas)[i].id = i + 1;
		(*phelas)[i].semname = ft_itoa(i + 1);
		(*phelas)[i].kushoet = semhndlr((*phelas)->semname, 1, NULL);
		(*phelas)[i].nkvd = nkvd;
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
	common.stamert = semhndlr("smert", 0, NULL);
	i = -1;
	while (++i < nkvd.numphelas)
	{
		phelas[i].pid = fork();
		if (!phelas[i].pid)
			what_a_wonderful_life(&meta, phelas[i].id, phelas[i].kushoet);
	}
	nkvd.officers = malloc(sizeof(*nkvd.officers) * nkvd.numphelas);
	i = -1;
	while (++i <= nkvd.numphelas)
		sem_post(common.stamert);
	watch(phelas, &nkvd);
	exit(0);
}
