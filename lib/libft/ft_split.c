/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfeve <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:35:04 by dfeve             #+#    #+#             */
/*   Updated: 2024/11/12 18:09:34 by dfeve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	calc_size(char const *s, char c)
{
	int	result;
	int	i;
	int	on_space;

	result = 0;
	i = 0;
	on_space = 0;
	while (s[i])
	{
		if (s[i] == c && on_space == 1)
		{
			on_space = 0;
		}
		else if (s[i] != c && on_space == 0)
		{
			result++;
			on_space = 1;
		}
		i++;
	}
	return (result);
}

static int	calc_end(char const *s, char c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (s[i] == c)
		i--;
	return (i + 1);
}

static void	set_var(unsigned int *a, int *b, int *c, int val)
{
	*a = val;
	*b = val;
	*c = val;
}

static int	set_on_space(int cond, int *on_space, char **result, int j)
{
	int	i;

	i = 0;
	if (cond == 1 && *on_space == 1)
	{
		j = j - 1;
		*on_space = 0;
	}
	else if (cond == 0 && *on_space == 0)
		*on_space = 1;
	(void)result;
	(void)j;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int				on_space;
	int				j;
	int				i;
	char			**result;
	unsigned int	start;

	result = malloc((calc_size(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	set_var(&start, &i, &j, 0);
	on_space = 0;
	while (s[i])
	{
		if (s[i] == c && on_space == 1)
			result[j++] = ft_substr(s, start, i - start);
		else if (s[i] != c && on_space == 0)
			start = i;
		if (set_on_space(s[i] == c, &on_space, result, j) == 1)
			return (NULL);
		i++;
	}
	if (on_space == 1)
		result[j++] = ft_substr(s, start, calc_end(s, c) - start);
	result[j] = NULL;
	return (result);
}
/*
int main()
{
	int	i;
	char	**s;
	i = 0;
	s = ft_split("  tripouille  42  ", ' ');
	printf("-------------------FINISHED FT_SPLIT-------------------\n");
	while (s[i] != NULL)
	{
		printf("%s\n", s[i]);
		i++;
	}
}*/
