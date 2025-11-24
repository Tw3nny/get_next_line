/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/24 02:55:12 by matisgutier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h> // open()

/* open() flags :
	- O_RDONLY : open the file and read only 
	- O_WRONLY : open the file and write only 
	- O_RDWR : open the file with read + write mode
	- O_CREAT : create a file if doesnt exist int the directory
	- O_EXCL : use it with O_CREAT, protection when create a file */

// cherche le \n 
char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == (char) c)
		return ((char *) &str[i]);
	return (0);
}
// lit la ligne jusqu'a tomber sur \n + return stash complet

char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	return (stash);
}

// si on trouve pas de newline dans set_line
char	*no_new_line(char **stash_ptr)
{
	char	*line;

	line = ft_strdup(*stash_ptr);
	free(*stash_ptr);
	*stash_ptr = NULL;
	return (line);
}

static char	*set_line(char **stash_ptr)
{
	char	*stash;
	char	*newline;
	char	*line;
	char	*tmp;
	int		len;

	stash = *stash_ptr;
	if (!stash || *stash == '\0')
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (!newline)
		return (no_new_line(stash_ptr));
	len = (newline - stash) + 1;
	line = ft_substr(stash, 0, len);
	tmp = stash;
	*stash_ptr = ft_substr(stash, len, ft_strlen(stash) - len);
	free(tmp);
	if (*stash_ptr && **stash_ptr == '\0')
	{
		free(*stash_ptr);
		*stash_ptr = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = set_line(&stash);
	return (line);
}
