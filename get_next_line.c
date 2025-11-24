/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/24 16:57:43 by matisgutier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
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
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == (char) c)
		return ((char *) &str[i]);
	return (NULL);
}
// lit la ligne jusqu'a tomber sur \n + return stash complet

char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!stash)
	{
		stash = NULL;
		return (NULL);
	}
	line = set_line(&stash);
	return (line);
}

/* int main(void)
{
    int     fd;
    char    *line;
    int     line_count;
    
    // Test 1: Fichier normal
    printf("=== TEST 1: Fichier normal ===\n");
    fd = open("test1.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open test1.txt");
        return (1);
    }
    line_count = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Ligne %d: [%s]", line_count++, line);
        free(line);
    }
    close(fd);
    
    // Test 2: Fichier vide
    printf("\n=== TEST 2: Fichier vide ===\n");
    fd = open("test5.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open test5.txt");
        return (1);
    }
    line = get_next_line(fd);
    if (line == NULL)
        printf("Retour NULL (correct pour fichier vide)\n");
    else
    {
        printf("Ligne: [%s]\n", line);
        free(line);
    }
    close(fd);
    
    // Test 3: Plusieurs appels successifs
    printf("\n=== TEST 3: Appels multiples ===\n");
    fd = open("test1.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("1er appel: [%s]", line);
    free(line);
    line = get_next_line(fd);
    printf("2ème appel: [%s]", line);
    free(line);
    line = get_next_line(fd);
    printf("3ème appel: [%s]", line);
    free(line);
    line = get_next_line(fd);
    if (line == NULL)
        printf("4ème appel: NULL (fin de fichier)\n");
    close(fd);
    
    // Test 4: Fichier sans \n final
    printf("\n=== TEST 4: Sans newline final ===\n");
    fd = open("test3.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("Ligne: [%s]\n", line);
    free(line);
    line = get_next_line(fd);
    if (line == NULL)
        printf("Ligne suivante: NULL (correct)\n");
    close(fd);
    
    // Test 5: FD invalide
    printf("\n=== TEST 5: FD invalide ===\n");
    line = get_next_line(-1);
    if (line == NULL)
        printf("FD invalide retourne NULL (correct)\n");
    
    // Test 6: Lecture multiple avec 2 FD différents
    printf("\n=== TEST 6: Deux FD en parallèle ===\n");
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    
    line = get_next_line(fd1);
    printf("FD1: [%s]", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("FD2: [%s]", line);
    free(line);
    
    line = get_next_line(fd1);
    printf("FD1: [%s]", line);
    free(line);
    
    close(fd1);
    close(fd2);
    
    printf("\n=== TOUS LES TESTS TERMINES ===\n");
    return (0);
} */