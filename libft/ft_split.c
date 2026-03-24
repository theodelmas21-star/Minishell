/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:31:48 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/24 09:53:38 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	*alloc_word(const char *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	word = ft_calloc(sizeof(char), (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static void	free_array(char **array, int last)
{
	while (last >= 0)
		free(array[last--]);
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = ft_calloc(sizeof(char *), (words + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < words)
	{
		while (*s == c)
			s++;
		array[i] = alloc_word(s, c);
		if (!array[i])
			return (free_array(array, i - 1), NULL);
		s += ft_strlen(array[i]);
		i++;
	}
	array[i] = NULL;
	return (array);
}
