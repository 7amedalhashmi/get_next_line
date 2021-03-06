/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halhashm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:32:14 by halhashm          #+#    #+#             */
/*   Updated: 2022/02/25 11:04:46 by halhashm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*new_sbuf(char *sbuf)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	if (!sbuf)
		return (NULL);
	while (sbuf[i] && sbuf[i] != '\n')
		i++;
	if (!sbuf[i])
	{
		free (sbuf);
		return (NULL);
	}
	new_buf = malloc(sizeof(char) * (ft_strlen(sbuf) - i + 1));
	if (!new_buf)
		return (NULL);
	i++;
	j = 0;
	while (sbuf[i])
		new_buf[j++] = sbuf[i++];
	new_buf[j] = '\0';
	free (sbuf);
	return (new_buf);
}

char	*return_new_line(char *sbuf)
{
	int		i;
	char	*ret_line;

	i = 0;
	if (!sbuf[i])
		return (NULL);
	while (sbuf[i] && sbuf[i] != '\n')
		i++;
	ret_line = malloc(sizeof(char) * (i + 2));
	if (!ret_line)
		return (NULL);
	i = 0;
	while (sbuf[i] && sbuf[i] != '\n')
	{
		ret_line[i] = sbuf[i];
		i++;
	}
	if (sbuf[i] == '\n')
	{
		ret_line[i] = sbuf[i];
		i++;
	}
	ret_line[i] = '\0';
	return (ret_line);
}

char	*readl(int fd, char *sbuf)
{
	char	*str;
	int		read_result;

	read_result = 1;
	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (!ft_strchr(sbuf, '\n') && read_result != 0)
	{
		read_result = read(fd, str, BUFFER_SIZE);
		if (read_result < 0)
		{
			free(str);
			return (NULL);
		}
		str[read_result] = '\0';
		sbuf = ft_strjoin(sbuf, str);
	}
	free(str);
	return (sbuf);
}

char	*get_next_line(int fd)
{
	static char	*sbuf[1024];
	char		*ret_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	sbuf[fd] = readl(fd, sbuf[fd]);
	if (!sbuf[fd])
	{
		free (sbuf[fd]);
		return (NULL);
	}
	ret_line = return_new_line(sbuf[fd]);
	sbuf[fd] = new_sbuf(sbuf[fd]);
	return (ret_line);
}
