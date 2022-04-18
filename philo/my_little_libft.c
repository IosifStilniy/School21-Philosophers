/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_little_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcelsa <dcelsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:57:03 by dcelsa            #+#    #+#             */
/*   Updated: 2022/04/18 22:57:07 by dcelsa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phelasafe.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		i++;
	write(fd, s, i);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = (unsigned char) c;
	i = 0;
	while (s[i])
		i++;
	while (i > 0)
		if (s[i--] == cc)
			return ((char *)&s[++i]);
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		res;

	i = 0;
	while (str && ((9 <= str[i] && str[i] <= 13) || str[i] == ' '))
		i++;
	sign = 1;
	if (str && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	res = 0;
	while (str && str[i] && '0' <= str[i] && str[i] <= '9')
		res = res * 10 + sign * (str[i++] - '0');
	return (res);
}
