/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matiguti <matiguti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:59:39 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/17 13:37:51 by matiguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
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

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	int		i;
	int		str_len;
	char	*substr;

	str_len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (start > str_len)
		return (malloc(1));
	if (start + str_len > len)
		len = str_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*strdup(char *str)
{
	int		i;
	int		size;
	char	*dup;

	size = ft_strlen(str);
	dup = malloc(size + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i],
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*join;

	if (!s1)
		return (malloc(1));
	len = ft_strlen(s1 + s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{

	}
}

