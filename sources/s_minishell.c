/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssteveli <ssteveli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:46:03 by ssteveli          #+#    #+#             */
/*   Updated: 2025/05/29 16:26:18 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_lexer(t_list **lex_temp)
{
	t_list	*lexer;

	lexer = *lex_temp;
	ft_printf("\n\nlexer string = ");
	while (lexer)
	{
		if (lexer->token != 0)
			ft_printf("%d -> ", lexer->token);
		else
			ft_printf("%s -> ", lexer->str);
		lexer = lexer->next;
	}
	ft_printf("\n----\n\n\n");
}

void	print_cmd(t_cmd **cmd_temp)
{
	t_cmd	*cmd;
	t_list	*redirection;
	int		i;

	i = 0;
	cmd = *cmd_temp;
	while (cmd)
	{
		ft_printf("str = ");
		while (cmd->str[i])
		{
			ft_printf("%s |", cmd->str[i]);
			i++;
		}
		ft_printf("\n");
		redirection = cmd->redirection;
		print_lexer(&redirection);
		cmd = cmd->next;
	}
}

char	*rl_gets(char *text)
{
	static char	*line_read;

	line_read = (char *) NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *) NULL;
	}
	line_read = readline(text);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void	free_free(t_list **lexer, t_cmd **cmd, t_data *data)
{
	free(data->echostr);
	data->echostr = NULL;
	free_lexer(lexer);
	lexer = NULL;
	free_cmd(cmd);
	cmd = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_list	**lexer;
	t_cmd	**cmd;
	t_data	*data;
	char	**str;

	(void)argc;
	(void)argv;
	init_minishell(&data, &cmd, envp);
	str = 0;
	while (1)
	{
		lexer = ft_kalloc(1, sizeof(t_list));
		data->lexer = lexer;
		if (launch_mini(str, data, cmd, lexer) == 0)
		{
			ft_printf("\b\bexit");
			free_data(data);
			free_all(lexer, cmd, str);
			exit(0);
		}
		free_free(lexer, cmd, data);
		free_all(lexer, cmd, NULL);
	}
	free_all(lexer, cmd, str);
	return (0);
}
