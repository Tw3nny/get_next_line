/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matiguti <matiguti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:59:39 by matisgutier       #+#    #+#             */
/*   Updated: 2025/11/17 14:49:47 by matiguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

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
		return (ft_strdup(""));
	if (start + len > str_len)
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

char	*ft_strdup(char *str)
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	
	tmp_dst = (unsigned char *) dst;
	tmp_src = (unsigned char *) src;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*join;

	if (!s1)
		ft_strdup("");
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, len_s1);
	ft_memcpy(join + len_s1, s2, len_s2);
	 join[len_s1 + len_s2] = '\0';
	free(s1);
	return (join);
}

