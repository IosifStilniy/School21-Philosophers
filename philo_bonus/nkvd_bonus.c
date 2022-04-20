#include "phelasafe_bonus.h"

static t_bool	morg(t_phela *phela, struct timeval tp[2], int *lastmeal, int *eatcount)
{
	if (timemachine(0, tp) > phela->nkvd->common->eattime * 90 / 100)
	{
		*lastmeal = 0;
		(*eatcount)++;
		if (*eatcount == phela->nkvd->eatcount)
			phela->nkvd->fulled++;
	}
	else
	{
		if (!timemachine(0, tp))
		{
			usleep(100);
			gettimeofday(&tp[1], NULL);
		}
		*lastmeal += timemachine(0, tp);
	}
	return (*lastmeal >= phela->nkvd->lifetime);
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
	lastmeal = tp[0].tv_sec * 1000 + tp[0].tv_usec / 1000;
	while (!phela->nkvd->dvuhsotiy || phela->nkvd->fulled < phela->nkvd->numphelas)
	{
		sem_wait(phela->kushoet);
		sem_post(phela->kushoet);
		gettimeofday(&tp[1], NULL);
		if (morg(phela, tp, &lastmeal, &eatcount))
			break ;
		gettimeofday(&tp[0], NULL);
	}
	if (phela->nkvd->dvuhsotiy || phela->nkvd->fulled == phela->nkvd->numphelas)
		return (NULL);
	sem_wait(phela->nkvd->common->stamert);
	logger(phela->nkvd->common, phela->id, LOGDTH);
	phela->nkvd->dvuhsotiy = TRUE;
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
	while (!nkvd->dvuhsotiy || nkvd->fulled < nkvd->numphelas)
		;
	i = -1;
	while (++i < nkvd->numphelas)
	{
		kill(phelas[i].pid, SIGINT);
		sem_close(phelas[i].kushoet);
		sem_unlink(phelas[i].semname);
		free(phelas[i].semname);
	}
	sem_close(nkvd->common->matyugalnik);
	sem_unlink("matyugalnik");
	free(nkvd->officers);
	free(phelas);
}
