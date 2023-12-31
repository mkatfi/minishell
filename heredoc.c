/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 23:32:42 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/19 17:03:21 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_herdoc(t_env *envp, char *lim, int *pipefd)
{
	char	*line;
	char	*line2;

	while (1)
	{
		line = readline("> ");
		line2 = ft_expand_value(line, envp);
		if (!line || !ft_strcmp(lim, line))
		{
			g_g.exit_status = 0;
			free(line);
			break ;
		}
		else if (!g_g.check && line2)
			line = ft_expand_value(line, envp);
		ft_putendl_fd(line, pipefd[1]);
		free(line);
	}
}

int	here_doc(char *lim, t_env *envp)
{
	int	status;
	int	pipefd[2];
	int	id;

	pipe(pipefd);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		read_herdoc(envp, lim, pipefd);
		exit(0);
	}
	signal(SIGINT, sig_handler);
	waitpid(id, &status, 0);
	if (WIFSIGNALED(status))
		return (-2);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	g_g.pipefd = pipefd[0];
	close(pipefd[1]);
	return (pipefd[0]);
}

char	**heredoc_without_quotes(char *words)
{
	int	i;

	if (g_g.str)
	{
		free(g_g.str);
	}
	g_g.str = malloc((count_strings(words) + 1) * sizeof(char *));
	g_g.k = 0;
	i = 0;
	while (words[i])
	{
		lim_check(words);
		if (empty_string_condition(words, &i))
			g_g.str[g_g.k] = empty_string(g_g.str[g_g.k], &i);
		else if ((words[i] == '\"' && words[i + 1] != '\"'))
			g_g.str[g_g.k] = fill_word_with_d_q(g_g.str[g_g.k], words, &i);
		else if ((words[i] == '\'' && words[i + 1] != '\''))
			g_g.str[g_g.k] = fill_word_with_s_q(g_g.str[g_g.k], words, &i);
		else if (words[i] != '\"' && words[i] != '\'')
			g_g.str[g_g.k] = fill_word_without_q(g_g.str[g_g.k], words, &i);
		g_g.k++;
	}
	g_g.str[g_g.k] = NULL;
	return (g_g.str);
}

void	skip_d_quotes(char *words, int *i, int *count)
{
	(*i)++;
	while (words[*i] && words[*i] != '\"')
		(*i)++;
	if (words[*i])
		(*i)++;
	(*count)++;
}

void	skip_s_quotes(char *words, int *i, int *count)
{
	(*i)++;
	while (words[*i] && words[*i] != '\'')
		(*i)++;
	if (words[*i])
		(*i)++;
	(*count)++;
}
