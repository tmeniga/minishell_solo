#include "minishell.h"

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
		if (is_str(temp->content))
			printf("string\n");
		i++;
    }
}