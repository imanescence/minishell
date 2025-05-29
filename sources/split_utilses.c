/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utilses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:45:45 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/29 15:47:55 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	error_quot(void)
{
	ft_printf("Error quote\n");
	exit (1);
}

int	is_dif(char c, char *str, int i)
{
	if (str[i] == c)
	{
		if (str[i] != c && str[i + 1] != c)
			return (1);
	}
	return (0);
}

int	is_export_case(char *str, int i)
{
	while (str[i] && str[i] != ' ')
	{
		if (str[i] == '=' && (str[i + 1] == '\"' || str[i + 1] == '\''))
			return (1);
		i++;
	}
	return (0);
}

int	len_to_sep_bis(int count, char *str, int i)
{
	int	quot;

	quot = 0;
	if (is_export_case(str, i) == 1)
	{
		count = 0;
		while (quot != 2)
		{
			if (str[i] == '\"' || str[i] == '\'')
				quot++;
			i++;
			count++;
		}
	}
	return (count);
}

int	len_to_sep(char *str, int i, char c)
{
	int	count;
	int	j;

	j = i;
	count = 0;
	if (c == '\'' || c == '\"')
	{
		if (str[i] && str[i + 1] == c)
			return (0);
		i++;
		while (str[i++] && str[i] != c)
			count++;
		return (count + 3);
	}
	else if (str[i] != ' ' && str[i] != '\t')
	{
		while (str[i] && (str[i] != ' ' && str[i] != '\t') && is_dif('\'', \
					str, i) == 0 && is_dif('\"', str, i) == 0)
		{
			count++;
			i++;
		}
		return (len_to_sep_bis(count, str, j));
	}
	return (0);
}
