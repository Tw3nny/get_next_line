/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/26 11:48:22 by matisgutier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> // open()
#define BUFFFER_SIZE 1

/* open() flags :
	- O_RDONLY : open the file and read only
	- O_WRONLY : open the file and write only
	- O_RDWR : open the file with read + write mode
	- O_CREAT : create a file if doesnt exist int the directory
	- O_EXCL : use it with O_CREAT, protection when create a file */

// cherche le \n
char	*ft_strchr(const char *str, int c)
{
	int i;
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
	ssize_t bytes_read;
	char	*tmp;
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
	}
	return (stash);
}
// si on trouve pas de newline dans set_line
char	*no_new_line(char **stash_ptr)
{
	char	*line;
	
	if (!*stash_ptr || **stash_ptr == '\0')
	{
		if (*stash_ptr)
			free(*stash_ptr);
		*stash_ptr = NULL;
		return (NULL);
	}
	line = ft_strdup(*stash_ptr);
	free(*stash_ptr);
	*stash_ptr = NULL;
	return (line);
}
static char *set_line(char **stash_ptr)
{
	char	*stash;
	char	*newline;
	char	*line;
	char	*tmp;
	int		len;
	stash = *stash_ptr;
	if (!stash || *stash == '\0')
		return (no_new_line(stash_ptr));
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
	static char *stash;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = set_line(&stash);
	return (line);
}

int main(void)
{
	int fd;
	char *line;
	
	system("printf '\\n\\n\\n\\n\\n' > test.txt");
	fd = open("test.txt", O_RDONLY);
	
	line = get_next_line(fd);
	printf("1: %s", line ? line : "NULL\n");
	free(line);
	
	line = get_next_line(fd);
	printf("2: %s", line ? line : "NULL\n");
	free(line);
	
	line = get_next_line(fd);
	printf("3: %s", line ? line : "NULL\n");
	free(line);
	
	line = get_next_line(fd);
	printf("4: %s", line ? line : "NULL\n");
	free(line);
	
	line = get_next_line(fd);
	printf("5: %s", line ? line : "NULL\n");
	free(line);
	
	line = get_next_line(fd);
	printf("6: %s", line ? line : "NULL\n");
	free(line);
	
	close(fd);
	unlink("test.txt");
	return (0);
}
