#include "minishell.h"

void    type_assigner(t_token *head)
{
    t_token *temp;
	
	while (head != NULL) 
	{
        temp = head;
        head = head->next;
        temp->type = get_type(temp->content);
    }
}

void    test(t_token *head)
{
    t_token *temp;

    while (head != NULL)
    {
        temp = head;
        head = head->next;
        //# if type is cmd, everything after is arg till diff type

        //#



    }

}

int     get_type(char *content)
{
    if (!ft_strncmp(content, "|", 1))
        return (PIPE);
	else if (!ft_strncmp(content, ">>", 2))
        return (APPEND);
	else if (!ft_strncmp(content, "<<", 2))
        return (HEREDOC);
	else if (!ft_strncmp(content, ">", 1))
        return (TRUNC);
	else if (!ft_strncmp(content, "<", 1))
        return (INPUT);
	else
        return (CMD);
}
