/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/20 12:09:29 by matisgutier      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> // open()

/* open() flags :
	- O_RDONLY : open the file and read only 
	- O_WRONLY : open the file and write only 
	- O_RDWR : open the file with read + write mode
	- O_CREAT : create a file if doesnt exist int the directory
	- O_EXCL : use it with O_CREAT, protection when create a file */

char	*get_next_line(int fd)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	/*   etape 2 :
	-2 : while != \n && != end of file(EOF) -> on lit la ligne
	   etape 3 :
	-3 : if |n(strchr) -> extraire la ligne(substr) + update static
	-4 : else if EOF return ce qui existe
	-5 : else if return NULL */
}

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
