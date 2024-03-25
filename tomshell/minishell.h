#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

//# linked list functions
t_token		*create_new_node(char *token);
void		append_node(t_token **head, char *token);
t_token		*create_linked_list(char *str);
void		free_linked_list(t_token *head);
void		print_linked_list(t_token *head);

//# lexer functions
char		*get_token(char *str, int x);
t_token		*lexer(char *str);

//# syntax check
int quote_checker(char *str);
int is_str(char *str);
int pipe_checker(char *str);
int redirect_check(char *str);
int	syntax_check(t_token *head);


//# prompter
void		prompter();

//# helper functions
int		get_next_quote(char *str,char c, int i);
int		is_space(char c);
int		is_quote(char c);
int		is_operator(char c);
char	*doublestring(char *str);
char	*ft_strdup1(char *str, int start, int end);


void					prompter();
int						main();

#endif