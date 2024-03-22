/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dscholz <dscholz@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:04:07 by dscholz           #+#    #+#             */
/*   Updated: 2024/03/04 09:30:07 by dscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pp
{
	char	**paths;
	char	**args1;
	char	**args2;
	char	*path1;
	char	*path2;
	int		pid1;
	int		pid2;
	int		outfile;
	int		infile;
	int		p[2];
	int		status;
	int		count;
	int		pipecount;
	int 	outfileflag;
}	t_pp;

void	child1(t_pp pp, char **env, char **av);
void	child2(t_pp pp, char **env, char **av);
void	pipexx(t_pp pp, char **av, char **env);
int		mainn(int ac, char **av, char **env);
void	fpaths(char **paths);
char	*tester(t_pp pp, char **args);
t_pp	paths(char **env, t_pp p, char **av);
void	execvefail(t_pp pp);
void	sfree(t_pp pp);
void	errinfile(t_pp pp, char **av);
void	erroutfile(t_pp pp, char **av);
void	zero(t_pp *pp);
void	args(t_pp *pp, char **av);
void	paths2(t_pp p);

#endif