#include "minishell.h"

//# function returns 1 if quotes are correct
//# returns 0 if there is a quote only at start or end
int quote_checker(char *str)
{
    int last_index;

    last_index = ft_strlen(str) - 1;
    if (str[0] == '\'' && str[last_index] != '\'')
        return (0);
    if (str[0] != '\'' && str[last_index] == '\'')
        return (0);
    if (str[0] == '\"' && str[last_index] != '\"')
        return (0);
    if (str[0] != '\"' && str[last_index] == '\"')
        return (0);
    return (1);
}

//# function returns 1 if str is in quotes
//# return 0 if not in quote
int is_str(char *str)
{
    int last_index;

    last_index = ft_strlen(str) - 1;
    if (str[0] == '\'' && str[last_index] == '\'')
        return (1);
    if (str[0] == '\"' && str[last_index] == '\"')
        return (1);
    return (0);
}

//# function returns 1 if str is in quotes so
//# the number of pipes doesn't matter
//# returns 1 if there is only 1 pipe
//# return 0 if there are multiple pipes
int pipe_checker(char *str)
{
    int i;
    int count;

    if (is_str(str))
        return (1);
    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        if (count > 1)
            return (0);
        i++;
    }
    return (1);
}

//# function returns 1 if str is in quotes so
//# the number of signs doesn't matter
//# returns 1 if syntax is correct
//# returns 0 if syntax is incorrect
int redirect_check(char *str)
{

    if (is_str(str))
        return (1);
    if (str[0] != '<' || str[0] != '>')
        return (1);
    if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, "<<", 2) == 0 || \
        ft_strncmp(str, ">>", 2) == 0 || ft_strncmp(str, ">", 1) == 0)
    {
        return (1);
    }
    return (0);
}




