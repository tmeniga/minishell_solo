#include "minishell.h"

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