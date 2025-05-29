/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:44:18 by ssteveli          #+#    #+#             */
/*   Updated: 2024/08/29 16:46:10 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_data(t_data *data)
{
	t_cmd	**cmds;

	cmds = data->cmd;
	free_lexer(data->lexer);
	free_all(data->lexer, data->cmd, NULL);
	free_strs(data->env);
	free(data->user);
	if (data->echostr)
	{
		free(data->echostr);
		data->echostr = NULL;
	}
	free(data);
	free(cmds);
}

int	free_all(t_list **lexer, t_cmd **cmd, char **str)
{
	(void)cmd;
	(void)lexer;
	free(str);
	return (0);
}

t_cmd	*free_cmd2(t_cmd **cmd, t_cmd *next, t_cmd *cmd2, t_list *temp)
{
	if (cmd2->str)
	{
		free(cmd2->str);
		cmd2->str = NULL;
	}
	if (cmd2->redirection)
	{
		while (cmd2->redirection)
		{
			temp = cmd2->redirection->next;
			if (cmd2->redirection->str && cmd2->redirection->str != NULL)
				cmd2->redirection->str = NULL;
			if (cmd2->redirection && cmd2->redirection != NULL)
				free(cmd2->redirection);
			cmd2->redirection = temp;
		}
	}
	free(cmd2);
	cmd2 = NULL;
	*cmd = cmd2;
	return (next);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*next;
	t_cmd	*cmd2;
	t_list	*temp;

	cmd2 = *cmd;
	while (cmd2)
	{
		next = cmd2->next;
		temp = 0;
		cmd2 = free_cmd2(cmd, next, cmd2, temp);
	}
}

void	free_lexer(t_list **lexer)
{
	t_list	*next;
	t_list	*lexer2;

	lexer2 = *lexer;
	while (lexer2)
	{
		next = lexer2->next;
		free(lexer2);
		lexer2 = NULL;
		lexer2 = next;
	}
	free(lexer);
	lexer = NULL;
}
