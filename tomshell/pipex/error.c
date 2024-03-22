/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 23:12:52 by dscholz           #+#    #+#             */
/*   Updated: 2024/01/19 12:46:41 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	errinfile(t_pp pp, char **av)
{
	if (pp.paths != 0)
		fpaths(pp.paths);
	if (pp.args1 != 0)
		fpaths(pp.args1);
	if (pp.args2 != 0)
		fpaths(pp.args2);
	if (pp.path1 != 0)
		free(pp.path1);
	if (pp.path2 != 0)
		free(pp.path2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(av[1], 2);
	ft_putstr_fd(": ", 2);
	perror("");
	exit(EXIT_SUCCESS);
}

void	erroutfile(t_pp pp, char **av)
{
	if (pp.paths != 0)
		fpaths(pp.paths);
	if (pp.args1 != 0)
		fpaths(pp.args1);
	if (pp.args2 != 0)
		fpaths(pp.args2);
	if (pp.path1 != 0)
		free(pp.path1);
	if (pp.path2 != 0)
		free(pp.path2);
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(av[4], 2);
	ft_putstr_fd(": ", 2);
	perror("");
	close(pp.p[0]);
	exit(EXIT_SUCCESS);
}

void	zero(t_pp *pp)
{
	pp->args1 = 0;
	pp->args2 = 0;
	pp->paths = 0;
	pp->path1 = 0;
	pp->path2 = 0;
}

void	execvefail(t_pp pp)
{
	perror("execve fail");
	fpaths(pp.args1);
	free(pp.path1);
	exit(EXIT_SUCCESS);
}
