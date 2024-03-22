/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:04:03 by dscholz           #+#    #+#             */
/*   Updated: 2024/01/21 14:42:34 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	fpaths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i] != 0)
		free(paths[i++]);
	free(paths);
	paths = 0;
}

void	sfree(t_pp pp)
{
	if (pp.paths != 0)
		fpaths(pp.paths);
	if (pp.args1 != 0)
		fpaths(pp.args1);
	if (pp.args2 != 0)
		fpaths(pp.args2);
	if (pp.path1 != 0)
	{
		free(pp.path1);
		pp.path1 = 0;
	}
	if (pp.path2 != 0)
	{
		free(pp.path2);
		pp.path2 = 0;
	}
	if (pp.p[0])
		close(pp.p[0]);
	if (pp.p[1])
		close(pp.p[1]);
	exit(EXIT_FAILURE);
}

char	*tester(t_pp pp, char **args)
{
	int		i;
	char	*t;
	char	*res;

	i = -1;
	while (pp.paths[++i] != NULL)
	{
		t = ft_strjoin(pp.paths[i], args[0]);
		if (!t)
			sfree(pp);
		if (access(t, X_OK) == 0)
		{
			res = t;
			return (res);
		}
		free(t);
	}
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command", 2);
	ft_putstr_fd(" not found\n", 2);
	return (0);
}

void	paths2(t_pp p)
{
	int		i;
	char	*temp;

	i = -1;
	while (p.paths[++i] != NULL)
	{
		temp = ft_strjoin(p.paths[i], "/");
		if (!temp)
			sfree(p);
		free(p.paths[i]);
		p.paths[i] = temp;
	}
	temp = ft_strtrim(p.paths[0], "PATH=");
	if (!temp)
		sfree(p);
	free(p.paths[0]);
	p.paths[0] = temp;
}

t_pp	paths(char **env, t_pp p, char **av)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			p.paths = ft_split(env[i], ':');
			if (!p.paths)
				exit(EXIT_FAILURE);
		}
	}
	if (!p.paths)
	{
		p.paths = (char **)malloc(2 * sizeof(char *));
		p.paths[0] = strdup(av[2]);
		p.paths[1] = strdup(av[3]);
	}
	paths2(p);
	return (p);
}
