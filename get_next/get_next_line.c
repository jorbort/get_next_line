/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbortolo <jbortolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:18:23 by jbortolo          #+#    #+#             */
/*   Updated: 2023/05/24 16:47:39 by jbortolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freee(char **str)
{
	free(*str);
	*str == NULL;
	return (NULL);
}

char	*parse_buff(int fd, char *arr_fd)
{
	int		i;
	char	*tmp_buff;

	i = 1;
	tmp_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp_buff)
		return (freee(&arr_fd));
	tmp_buff[0] = '\0';
	while (i > 0 && ft_strchr(tmp_buff, '\n') == 0)
	{
		i = read(fd, arr_fd, BUFFER_SIZE);
		if (i > 0)
		{
			tmp_buff[i] = '\0';
			arr_fd = ft_strjoin(arr_fd, tmp_buff);
		}
	}
	free(tmp_buff);
	if (i == -1)
		return (freee(&arr_fd));
	return (arr_fd);
}

char	*get_next_line(int fd)
{
	static char	*arr_fd[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (NULL);
	if (arr_fd[fd] && ft_strchr(arr_fd[fd], '\n') == 0)
		arr_fd[fd] = parse_buff(fd, arr_fd[fd]);
	if (!arr_fd[fd])
		return (NULL);
	line = next_l(arr_fd[fd]);
	if (!line)
		return (freee(&arr_fd[fd]));
	arr_fd[fd] = empty(arr_fd[fd]);
}
