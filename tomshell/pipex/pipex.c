/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:30:49 by dscholz           #+#    #+#             */
/*   Updated: 2024/02/28 13:49:01 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pp pp, char **env, char **av)
{
	if (close(pp.p[0]) == -1)
		sfree(pp);
	if (dup2(pp.p[1], STDOUT_FILENO) == -1)
		sfree(pp);
	close(pp.p[1]);
	pp.infile = open(av[1], O_RDONLY, 0777);
	if (pp.infile == -1)
		errinfile(pp, av);
	if (dup2(pp.infile, STDIN_FILENO) == -1)
		sfree(pp);
	fpaths(pp.paths);
	free(pp.path2);
	fpaths(pp.args2);
	close(pp.infile);
	if (execve(pp.path1, pp.args1, env) == -1)
		execvefail(pp);
}

void	child2(t_pp pp, char **env, char **av)
{
	close(pp.p[1]);
	if (dup2(pp.p[0], STDIN_FILENO) == -1)
		sfree(pp);
	if (pp.path1 == 0)
		close(pp.p[0]);
	pp.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pp.outfile == -1)
		erroutfile(pp, av);
	if (dup2(pp.outfile, STDOUT_FILENO) == -1)
		sfree(pp);
	close(pp.outfile);
	close(pp.p[0]);
	if (pp.path2 != 0)
	{
		if (!execve(pp.path2, pp.args2, env))
			perror("excev");
	}
}

void	pipexx(t_pp pp, char **av, char **env)
{
	if (pp.path1 != 0)
	{
		pp.pid1 = fork();
		if (pp.pid1 == -1)
			sfree(pp);
		if (pp.pid1 == 0)
			child1(pp, env, av);
	}
	pp.pid2 = fork();
	if (pp.pid2 == -1)
		sfree(pp);
	if (pp.pid2 == 0)
		child2(pp, env, av);
	close(pp.p[0]);
	close(pp.p[1]);
	if (pp.path1 != 0)
		waitpid(pp.pid1, &pp.status, 0);
	waitpid(pp.pid2, &pp.status, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	sfree(pp);
}

void	args(t_pp *pp, char **av)
{
	pp->args1 = ft_split(av[2], ' ');
	if (!pp->args1)
		sfree(*pp);
	if (!pp->args1[0])
	{
		free(pp->args1);
		pp->args1 = (char **)malloc(2 * sizeof(char *));
		if (!pp->args1)
			sfree(*pp);
		pp->args1[0] = ft_strdup(av[2]);
		if (!pp->args1[0])
			sfree(*pp);
		pp->args1[1] = 0;
	}
}

int	mainn(int ac, char **av, char **env)
{
	t_pp	pp;

	zero(&pp);
	if (ac != 5)
	{
		write(2, "./pipex infile ''cmd1'' ''cmd2'' outfile\n", 41);
		return (0);
	}
	if (pipe(pp.p) == -1)
		return (0);
	pp = paths(env, pp, av);
	args(&pp, av);
	if (access(av[2], X_OK) == 0 && (ft_strncmp(pp.args1[0], " ", 1) != 0))
		pp.path1 = ft_strdup(av[2]);
	else
		pp.path1 = tester(pp, pp.args1);
	pp.args2 = ft_split(av[3], ' ');
	if (!pp.args2)
		sfree(pp);
	if (access(av[3], X_OK) == 0)
		pp.path2 = ft_strdup(av[3]);
	else
		pp.path2 = tester(pp, pp.args2);
	pipexx(pp, av, env);
	return (0);
}
