/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhassani <mhassani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:25:12 by mkatfi            #+#    #+#             */
/*   Updated: 2023/07/19 16:02:43 by mhassani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(int k, int i)
{
	char	*cwd;

	cwd = malloc(sizeof(char) * 1000);
	if (getcwd(cwd, 1000) != NULL)
	{
		g_g.exit_status = 0;
		if (k)
			ft_putendl_fd(cwd, i);
		else
			return (cwd);
	}
	else
	{
		perror("getcwd error");
		g_g.exit_status = 1;
	}
	free(cwd);
	return (NULL);
}
