/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 15:20:08 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/03/09 19:08:19 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*check_return(char **s, int bytes)
{
	int		counter;
	char	*ret;
	char	*tmp;

	if (*s == NULL || bytes == -1)
		return (NULL);
	counter = find_nl(*s);
	if (counter != -1)
	{
		ret = ft_substr(*s, 0, counter);
		tmp = ft_substr(*s, counter + 1, ft_strlen(*s));
		free(*s);
		*s = tmp;
		if (**s != '\0')
			return (ret);
	}
	else
		ret = ft_strdup(*s);
	free(*s);
	*s = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*s[OPEN_MAX];
	int			bytes;
	char		storage[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bytes = read(fd, storage, BUFFER_SIZE);
	while (bytes > 0)
	{
		storage[bytes] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup("");
		tmp = ft_strjoin(s[fd], storage);
		free(s[fd]);
		s[fd] = tmp;
		if (find_nl(s[fd]) != -1)
			break ;
		bytes = read(fd, storage, BUFFER_SIZE);
	}
	return (check_return(&s[fd], bytes));
}

// int main()
// {
// 	int fd;
// 	char *line;
// 	fd = open("test.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line (fd);
// 		if (line == NULL)
// 			break ;
// 		printf("%s" , line);
// 	}
// }
