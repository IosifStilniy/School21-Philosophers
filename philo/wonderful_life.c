#include "phelasafe.h"

static void jrat(t_phela *phela, int curtime)
{
	struct timeval	tp;

	if (phela->lastmeal >= phela->meta->lifetime)
		return ;
	logger(curtime, phela->id, LOGTNK);
	pthread_mutex_lock(&phela->meta->forks[phela->id - 1]);
	pthread_mutex_lock(&phela->meta->forks[phela->id * (phela->id != phela->meta->numphelas)]);
	if (phela->lastmeal >= phela->meta->lifetime)
		return ;
	gettimeofday(&tp, NULL);
	curtime = tp.tv_sec - phela->meta->ad;
	logger(curtime, phela->id, LOGEAT);
	phela->kushoet = TRUE;
	usleep(phela->meta->eattime * 1000);
	phela->kushoet = FALSE;
	phela->lastmeal = 0;
	pthread_mutex_unlock(&phela->meta->forks[phela->id - 1]);
	pthread_mutex_unlock(&phela->meta->forks[phela->id * (phela->id != phela->meta->numphelas)]);
	logger(curtime + phela->meta->eattime, phela->id, LOGSLP);
	usleep(phela->meta->sleeptime * 1000);
}

void	*what_a_wonderful_life(void *arg)
{
	struct timeval	tp;
	t_phela			*phela;

	phela = (t_phela *)arg;
	gettimeofday(&tp, NULL);
	phela->birthday = tp.tv_sec;
	phela->lastmeal = 0;
	phela->eatcount = 0;
	while (1)
	{
		if (phela->meta->appocalipsis || phela->lastmeal >= phela->meta->lifetime)
			return (NULL);
		gettimeofday(&tp, NULL);
		jrat(phela, tp.tv_sec - phela->meta->ad);
	}
	return (NULL);
}
