/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:10:55 by jeongrol          #+#    #+#             */
/*   Updated: 2023/09/09 17:26:37 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

size_t	ft_strlen(const char *str)
{
	int	temp;

	temp = 0;
	if (str == NULL)
		return (temp);
	while (str[temp])
	{
		temp++;
	}
	return (temp);
}

int	ft_two_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*add;

	i = ft_strlen(src);
	add = (char *)malloc(sizeof(char) * (i + 1));
	if (!add)
		return (0);
	i = 0;
	while (src[i])
	{
		add[i] = src[i];
		i++;
	}
	add[i] = '\0';
	return (add);
}

char	*ft_exp_strdup(const char *src)
{
	int		exp_len;
	char	*add;
	char	*tmp;
	int		i;
	int		j;
	int		flag;

	exp_len = ft_strlen(src) + 13;
	add = (char *)malloc(sizeof(char) * (exp_len + 1));
	if (!add)
		return (0);
	tmp = "declare -x ";
	i = 0;
	j = 0;
	flag = 0;
	while (i < exp_len)
	{
		if (i < 11)
			add[i] = tmp[i];
		else
		{
			if (i == exp_len -1)
				add[i] = '"';
			else
			{
				add[i] = src[j];
				if (src[j] == '=' && flag == 0)
				{
					add[++i] = '"';
					flag = 1;
				}
			}
			j++;
		}
		i++;
	}
	add[i] = '\0';
	return (add);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] - s2[i] == 0)
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (0);
}

void ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

long long	ft_atoi(const char *str)
{
	int				sign;
	long long		value;
	int				i;

	sign = 1;
	value = 0;
	i = 0;
	if (str[0] == '+') 
		i++;
	else if (str[0] == '-')
	{
		i++;
		sign = -1;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		value = value * 10;
		value = value + str[i] - 48;
		i++;
	}
	return (sign * value);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len;
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i + j] = s2[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
