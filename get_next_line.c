/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmargart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 13:43:54 by dmargart          #+#    #+#             */
/*   Updated: 2020/12/14 13:43:56 by dmargart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		n_srch(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int		if_tail(char *buf, char **line)
{
	int		i;
	char	*tmp;

	if (buf)
	{
		tmp = *line;
		if ((i = n_srch(buf)) != -1)
		{
			buf[i] = '\0';
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			free(tmp);
			ft_strcpy(buf, &buf[++i]);
			return (1);
		}
		else
		{
			if (!(*line = ft_strjoin(*line, buf)))
				return (-1);
			free(tmp);
			buf[0] = '\0';
		}
	}
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*buf;
	int			i;
	int			ret;

	i = 0;
	if (BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	if (!(*line = ft_strdup("")))
		return (-1);
	if ((i = if_tail(buf, line) != 0))
		return (i);
	if (buf)
		free(buf);
	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		if ((i = if_tail(buf, line) != 0))
			return (i);
	}
	free(buf);
	buf = NULL;
	return (0);
}
