/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/26 11:09:57 by matisgutier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdio.h>
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

int main(void)
{
    int fd;
    char *line;
    int count = 0;
    
    // Créer le fichier de test
    system("printf '\\n\\n\\n\\n\\n\\n' > test_multiple_nl.txt");
    
    fd = open("test_multiple_nl.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("❌ Erreur: impossible d'ouvrir le fichier\n");
        return 1;
    }
    
    printf("=== TEST MULTIPLE_NL (BUFFER_SIZE = %d) ===\n\n", BUFFER_SIZE);
    
    while (1)
    {
        line = get_next_line(fd);
        count++;
        
        if (line == NULL)
        {
            printf("Appel %d: NULL\n", count);
            break;
        }
        
        printf("Appel %d: ", count);
        
        if (line[0] == '\n' && line[1] == '\0')
            printf("\"\\n\" ✅\n");
        else if (line[0] == '\0')
            printf("\"\" ❌ (devrait être NULL)\n");
        else
        {
            printf("\"");
            for (int i = 0; line[i]; i++)
            {
                if (line[i] == '\n')
                    printf("\\n");
                else
                    printf("%c", line[i]);
            }
            printf("\"\n");
        }
        
        free(line);
    }
    
    printf("\n=== RÉSULTAT ATTENDU ===\n");
    printf("Appel 1-6: \"\\n\"\n");
    printf("Appel 7: NULL\n");
    
    close(fd);
    unlink("test_multiple_nl.txt");
    
    return 0;
}
