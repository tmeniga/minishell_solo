#include "minishell.h"

int	get_next_quote(char *str,char c, int i);

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32 )
		return (1);
	return (0);
}

int is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

char	*doublestring(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*res; 

	i = 0;
	j = 0;
	len	= 2 * strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	while (str[j])
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

//# function that duplicates a string
//# from start_pos till end_pos
char	*ft_strdup1(char *str, int start, int end)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = end - start;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

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


int	get_next_quote(char *str, char c, int i)
{
	if (!str[i+1])
		return (i+1);
	i++;
	while (str[i])
	{
		if (str[i] == c)
			return (i+1);
		i++;
	}		
	return (i);
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



//# function creates a new node and stores token inside
//# return NULL incase of malloc error
t_token	*create_new_node(char *token)
{
	t_token *new_node;
	
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return NULL;
	new_node->content = token;
	new_node->next = NULL;
	return (new_node);
}

//# this function adds a node to the linked list
//# missing error handling if malloc in create_new_node() fails!
void	append_node(t_token **head, char *token)
{
	t_token	*new_node;
	t_token	*current;

	new_node = create_new_node(token);
	if (!new_node)
		return ; //handle error
	if (*head == NULL)
		*head = new_node;
	else 
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

//# this function creates a linked list
//# evertime it gets a new token from get_token(),
//# it adds a new element to the list, which contains a token
t_token		*create_linked_list(char *str)
{
	t_token	*head;
	char	*token;
	//char	*doublestr;
	int i = 0;

	//doublestr = doublestring(str);
	head = NULL;
	token = get_token(str, 0);
	append_node(&head, token);
	printf("token %s\n", token);
	while ((token = get_token(str, 1)) != NULL)
	{
		append_node(&head, token);
		printf("token %s\n", token);
		i++;
	}

	//error handling
	//if (...)

	return (head);
}

void	free_linked_list(t_token *head) 
{
	t_token *temp;
	
	while (head != NULL) 
	{
        temp = head;
        head = head->next;
        free(temp->content); // Free the string
        free(temp); // Free the node
    }
}

void	print_linked_list(t_token *head) 
{
	t_token *temp;
	int	i;
	
	i = 1;
	while (head != NULL) 
	{
        temp = head;
        head = head->next;
		printf("str %d: $%s$\n", i, temp->content);
		i++;
    }
}

t_token *lexer(char *str)
{
	t_token *head;

	head = create_linked_list(str);

	//# check_syntax(t_token *head)
	//# assign_type(t_token *head)
	
	return (head);
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
