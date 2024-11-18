/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bazaluga </var/spool/mail/bazaluga>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:38 by bazaluga          #+#    #+#             */
/*   Updated: 2024/11/18 18:50:39 by bazaluga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	l;
	int	i;

	i = 0;
	l = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			l++;
		while (s[i] != c && s[i])
			i++;
	}
	return (l);
}

static int	ft_fill_split(char **split, char const *s, char c, int l)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < l)
	{
		while (s[j] == c && s[j])
			j++;
		k = 0;
		while (s[j + k] != c && s[j + k])
			k++;
		split[i] = malloc2((k + 1) * sizeof(char));
		if (!split[i])
			return (0);
		k = 0;
		while (s[j] != c && s[j])
			split[i][k++] = s[j++];
		split[i][k] = '\0';
		i++;
	}
	split[l] = NULL;
	return (1);
}

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free2(split[i]);
		i++;
	}
	free2(split);
}

char	**gc_split(char const *s, char c)
{
	int		l;
	char	**split;

	if (!s)
		return (NULL);
	l = ft_count_words(s, c);
	split = (char **) malloc2((l + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (!ft_fill_split(split, s, c, l))
	{
		ft_free_split(split);
		return (NULL);
	}
	return (split);
}
