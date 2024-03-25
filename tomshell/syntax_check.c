#include "minishell.h"

	quote_checker(); // if quote at beginning, then also at end
	pipe_checker();	// only one pipe symbal if outside of string
	smaller_bigger_sign();	// correct redirect signs, ...   if outside of str
	flag_check();	// flag hast to start with - and can have nothing else than letters

int quote_checker(char *str)
{
    int last_index;

    last_index = strlen(str) - 1;
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

int is_str(char *str)
{
    int last_index;

    last_index = strlen(str) - 1;
    if (str[0] == '\'' && str[last_index] == '\'')
        return (1);
    if (str[0] == '\"' && str[last_index] == '\"')
        return (1);
    return (0);
}

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
            
    }



}