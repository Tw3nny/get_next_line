/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matisgutierreztw3nny <matisgutierreztw3    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:58:35 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/14 13:58:35 by matisgutier      ###   ########.fr       */
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

}
