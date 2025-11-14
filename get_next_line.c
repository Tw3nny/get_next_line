/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matiguti <matiguti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/14 17:27:28 by matiguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> // open()

/* open() flags :
	- O_RDONLY : open the file and read only 
	- O_WRONLY : open the file and write only 
	- O_RDWR : open the file with read + write mode
	- O_CREAT : create a file if doesnt exist int the directory
	- O_EXCL : use it with O_CREAT, protection when create a file */

char	*get_next_line(int fd)
{
	/* etape 1 :
	-1 : check if fd >= 0 and BUFFER_SIZE > 0
			read(fd, 0, 0) -> error ?
	   etape 2 :
	-2 : while != \n && != end of file(EOF) -> on lit la ligne
	   etape 3 :
	-3 : if |n(strchr) -> extraire la ligne(substr) + update static
	-4 : else if EOF return ce qui existe
	-5 : else if return NULL */
}
