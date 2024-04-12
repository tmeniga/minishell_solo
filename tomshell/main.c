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

	if (!syntax_check(head))
	{
		free_linked_list(head);
		exit(0);
	}

	//# check_syntax(t_token *head)
	//# assign_type(t_token *head)
	
	return (head);
}

int	syntax_check(t_token *head)
{
	t_token *temp;

	while (head != NULL) 
	{
        temp = head;
        head = head->next;
		if (!quote_checker(temp->content))
		{
			printf("SYNTAX ERROR: wrong quotes\n");
			return (0);
		}
		if (!pipe_checker(temp->content))
		{
			printf("SYNTAX ERROR: too many pipe symbols\n");
			return (0);
		}
		if (!redirect_check(temp->content))
		{
			printf("SYNTAX ERROR: wrong redirect syntax\n");
			return (0);
		}
    }
	return (1);
}

void	prompter()
{
	char	*input;
	t_token	*head;

	input = readline("tomshell> ");

	if(!input || !ft_strncmp(input, "exit", 5))
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