#include "minishell.h"

//# this functions return token from the string
//# everytime you call it gives you the next token
//# if a malloc fails this function return NULL
//# which means you have to free the linked list
//# if the function reaches the end of the string it returns doublestring(str)
//! also split flags (eg. -r)
char	*get_token(char *str, int x)
{
	static int	i;
	int			start;

	if (x == 0)
		i = 0;
	while (str[i])
	{
		while (is_space(str[i]) && str[i])
			i++;
		start = i;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = get_next_quote(str, str[i], i);
			return (ft_strdup1(str, start, i));
		}		
		start = i;
		while (!is_space(str[i]) && !is_operator(str[i]) && !is_quote(str[i]) && str[i])
			i++;
		if (start != i)
			return (ft_strdup1(str, start, i));
		
		start = i;
		while (is_operator(str[i]) && str[i])
			i++;
		if (start != i)
			return (ft_strdup1(str, start, i));
	}
	// return (doublestring(str));
	return (NULL);
}

t_token	*lexer(char *str)
{
	t_token *head;

	head = create_linked_list(str);

	syntax_check(head);
	

	//# check_syntax(t_token *head)
	//# assign_type(t_token *head)
	
	return (head);
}

int	syntax_check(t_token *head)
{
	quote_checker(); // if quote at beginning, then also at end
	pipe_checker();	// only one pipe symbal if outside of string
	smaller_bigger_sign();	// correct redirect signs, ...   if outside of str
	flag_check();	// flag hast to start with - and can have nothing else than letters
	






}

void	prompter()
{
	char	*input;
	t_token	*head;

	input = readline("tomshell> ");

	if(!input)
	{
		printf("exiting shell\n");
		exit(0);
	}

	head = lexer(input);
	if (!head)
	{
		printf("ERROR\n");
		return;
	}
	print_linked_list(head);

	//# create command table
	//# return command table
}

//# get constant user input with readline  -> prompter();
		//# inside prompter
				//# put input into cmdtable
				//# return cmdtable
//# execute cmdtable 

int	main()
{
	//t_cmdtable cmdtable;
	
	while(1)
	{
		prompter();
		// executer(cmdtable);
	}
	
	return (0);
}




























































































































/* char	*get_token(char *str, int x)
{
	static int	i;
	int			start;

	if (x == 0)
		i = 0;
	while (str[i])
	{
		while (is_space(str[i]) && str[i])
			i++;
		start = i;
		while (!is_space(str[i]) && !is_operator(str[i]) && str[i])
			i++;
		if (start != i)
			return (ft_strdup1(str, start, i));
		start = i;
		while (is_operator(str[i]) && str[i])
			i++;
		if (start != i)
			return (ft_strdup1(str, start, i));
	}
	// return (doublestring(str));
	return (NULL);
} */