#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "pipex/pipex.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# define NONE 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define HEREDOC 5
# define INPUT 6
# define PIPE 7
# define END 8

typedef struct s_token
{
	int					type;
	char				*content;
	struct s_token		*next;
}						t_token;

typedef struct s_cmdtable
{
	int					index;
	char				*cmd;
	char				**args;
	int					input;
	int					output;
	struct s_cmdtable	*next;
}						t_cmdtable;

// typedef struct s_cmdtable
// {
// 	char				*cmd;
// 	char				**args;
// 	char				*input;
// 	char				*output;
// 	int					type;
// 	struct s_cmdtable	*next;
// 	struct s_cmdtable	*prev;
// }						t_cmdtable;

void					prompter();
int						main();

#endif