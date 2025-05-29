/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:32:41 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/26 12:39:38 by ssteveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

void	*ft_kalloc(int num, int size)
{
	char	*str;

	str = ft_calloc(num, size);
	if (!str)
	{
		ft_printf("Malloc error\n");
		exit(0);
	}
	return (str);
}

t_list	*is_t(t_list **lexer)
{
	t_list	*temp;
	t_list	*prev_red;
	t_list	*temp_lexer;

	prev_red = 0;
	temp_lexer = *lexer;
	temp = 0;
	return (is_token_bis(temp, prev_red, temp_lexer));
}

char	**is_s(t_list **lexer)
{
	int		i;
	char	**str;
	t_list	*temp;
	t_list	*temp_lexer;

	i = 0;
	temp_lexer = *lexer;
	temp = temp_lexer;
	while (temp && temp->token != Pipe)
	{
		i++;
		temp = temp->next;
	}
	temp = temp_lexer;
	str = ft_kalloc(i + 1, sizeof(char *));
	if (str == 0)
		return (0);
	i = -1;
	while (temp && temp->token != Pipe)
	{
		str[++i] = temp->str;
		temp = temp->next;
	}
	return (str);
}
