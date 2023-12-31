/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:53:19 by mhassani          #+#    #+#             */
/*   Updated: 2023/07/21 16:04:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**strings_without_quotes(char *words, t_env *envp)
{
	char	**str;

	str = malloc((count_strings(words) + 1) * sizeof(char *));
	g_g.k = 0;
	g_g.t = 0;
	while (words[g_g.t])
	{
		if (empty_string_condition(words, &g_g.t))
			str[g_g.k] = empty_string(str[g_g.k], &g_g.t);
		else if ((words[g_g.t] == '\"' && words[g_g.t + 1] != '\"'))
		{
			str[g_g.k] = fill_word_with_d_q(str[g_g.k], words, &g_g.t);
			str[g_g.k] = fill_expand(str[g_g.k], envp);
		}
		else if ((words[g_g.t] == '\'' && words[g_g.t + 1] != '\''))
			str[g_g.k] = fill_word_with_s_q(str[g_g.k], words, &g_g.t);
		else if (words[g_g.t] != '\"' && words[g_g.t] != '\'')
		{
			str[g_g.k] = fill_word_without_q(str[g_g.k], words, &g_g.t);
			str[g_g.k] = fill_expand_without_q(str[g_g.k], envp);
		}
		g_g.k++;
	}
	str[g_g.k] = NULL;
	return (str);
}

char	*join_strings_to_be_one(char *words, t_env *envp)
{
	int		i;
	char	*joined_string;
	char	**to_be_joined;
	char	*temp;
	char	*x;

	i = 0;
	joined_string = words;
	to_be_joined = strings_without_quotes(words, envp);
	if (to_be_joined[i])
	{
		joined_string = ft_strdup(to_be_joined[i]);
		while (to_be_joined[i + 1])
		{
			x = joined_string;
			temp = ft_strjoin(joined_string, to_be_joined[i + 1]);
			joined_string = temp;
			free(x);
			i++;
		}
	}
	freepath(to_be_joined);
	return (joined_string);
}

void	minishell(t_data *data, char *cmd, t_env *envp)
{
	data->error = 0;
	data->flag = 0;
	syntax_errors(cmd, data);
	if (!data->error)
	{
		if (g_g.command)
			free(g_g.command);
		g_g.command = space_arround_red(cmd);
		replace_pipe_in_quotes(g_g.command);
		g_g.tokens = split_with_pipe(g_g.command);
		g_g.l = 0;
		g_g.expand = 0;
		g_g.ptr = NULL;
		while (g_g.tokens[g_g.l])
		{
			export_expand_case(envp);
			replace_space_in_quotes(g_g.tokens[g_g.l]);
			g_g.words = split_with_space(g_g.tokens[g_g.l]);
			ft_lstadd_token(&g_g.ptr, ft_lstnew_token(g_g.words, envp));
			freepath(g_g.words);
			g_g.l++;
		}
		freepath(g_g.tokens);
		infos_without_quotes(&g_g.ptr, envp);
	}
}

t_env	*fill_environment(int ac, char **av, char **envp)
{
	t_env	*env;
	int		h;

	(void)ac;
	(void)av;
	g_g.data = malloc(sizeof(t_data));
	if (!g_g.data)
		return (NULL);
	env = NULL;
	h = 0;
	while (envp && envp[h])
	{
		ft_lstadd_back_env(&env, ft_lstnew_env(envp[h]));
		h++;
	}
	g_g.exit_status = 0;
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = fill_environment(ac, av, envp);
	while (1)
	{
		g_g.signal_check = 0;
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		g_g.cmd = readline("minishell-3.2$ ");
		if (!g_g.cmd)
		{
			write(1, "exit\n", 5);
			free(g_g.cmd);
			g_g.exit_status = 0;
			exit(g_g.exit_status);
		}
		if (ft_strlen(g_g.cmd) > 0)
			add_history(g_g.cmd);
		minishell(g_g.data, g_g.cmd, env);
		if (g_g.signal_check == 0)
			chaeck_builtins1(&env, g_g.ptr);
		ft_free_data(&g_g.ptr);
		free(g_g.cmd);
	}
	return (0);
}
