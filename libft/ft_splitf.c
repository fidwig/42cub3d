/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsommet <jsommet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:27:06 by jsommet           #+#    #+#             */
/*   Updated: 2024/11/11 13:27:07 by jsommet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	count_wordsf(char const *s, int (*f)(int))
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 && !f(s[i])) || (i > 0 && !f(s[i]) && f(s[i - 1])))
			words++;
		i++;
	}
	return (words);
}

static size_t	len_word(char **s, int (*f)(int))
{
	size_t	len;

	while (**s && f(**s))
		(*s)++;
	len = 0;
	while ((*s)[len] && !f((*s)[len]))
		len++;
	return (len);
}

static void	*big_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	return (NULL);
}

char	**ft_splitf(char const *s, int (*f)(int))
{
	size_t	words;
	size_t	len;
	size_t	i;
	char	*tmp;
	char	**arr;

	if (!s)
		return (NULL);
	words = count_wordsf(s, f);
	arr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = (char *)s;
	i = 0;
	while (i < words)
	{
		len = len_word(&tmp, f);
		arr[i] = (char *)ft_calloc(len + 1, sizeof(char));
		if (!arr[i])
			return (big_free(arr));
		ft_strlcpy(arr[i], tmp, len + 1);
		tmp += len;
		i++;
	}
	return (arr);
}
