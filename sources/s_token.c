/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:47:07 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/20 14:12:24 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

void	sign_quit(int code)
{
	char	*str;

	if (g_glob.in_heredoc == 1)
	{
		str = ft_itoa(code);
		write(1, " Quit: ", 6);
		write(1, str, ft_strlen(str));
		write(1, "\n", 1);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
	}
}

void	sign_handler(int code)
{
	if (code == SIGINT)
	{
		if (g_glob.in_heredoc != 1)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			write(1, "\n", 1);
	}
}

t_list	*get_lexer_bis(t_list **lexer, char **a, t_list *prev, int i)
{
	if (ft_strncmp(a[i], ">>", 2) == 0)
	{
		prev = ft_lstnew(APPEND, 0, i, prev);
		ft_lstadd_back(lexer, prev);
	}
	else if (ft_strncmp(a[i], "<<", 2) == 0)
	{
		prev = ft_lstnew(HEREDOC, 0, i, prev);
		ft_lstadd_back(lexer, prev);
	}
	else if (ft_strncmp(a[i], ">", 2) == 0 || ft_strncmp(a[i], " >", 3) == 0)
	{
		prev = ft_lstnew(TRUNC, 0, i, prev);
		ft_lstadd_back(lexer, prev);
	}
	else
	{
		prev = ft_lstnew(Not_a_token, a[i], i, prev);
		ft_lstadd_back(lexer, prev);
	}
	return (prev);
}

t_list	**lexer_condi(t_list **lexer)
{
	if ((*lexer))
	{
		while (*lexer)
		{
			free(*lexer);
			(*lexer) = (*lexer)->next;
		}
	}
	return (lexer);
}

void	get_lexer(t_list **lexer, char **a)
{
	int		i;
	t_list	*prev;

	lexer = lexer_condi(lexer);
	i = -1;
	while (a[++i])
	{
		if (ft_strncmp(a[i], "|", 1) == 0)
		{
			prev = ft_lstnew(Pipe, 0, i, prev);
			ft_lstadd_back(lexer, prev);
		}
		else if (ft_strncmp(a[i], "<", 2) == 0)
		{
			prev = ft_lstnew(INPUT, 0, i, prev);
			ft_lstadd_back(lexer, prev);
		}
		else
			prev = get_lexer_bis(lexer, a, prev, i);
	}
}
