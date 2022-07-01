#include"minishell.h"

int	ft_cmp(char *s, char c)
{
	int count;
	int	i;

	i = 0;
	count = 0;
	while(s[i])
	{
		if(s[i] == c)
			count++;
		i++; 
	}
	return(count);
}

int	handle_quotes(char *s)
{	
	int i;

	i = 0;
	while(s[i])
	{
		if(s[i] == '"' || s[i] == 39)
		{
			if(ft_cmp(s, s[i]) == 2)
				break;
			else
				return(0);
		}
		i++;
	}
	return(1);
}

char	quotes_exist(char *argv, size_t *i)
{
	while(argv[*i])
	{
		if(argv[*i] == '"' || argv[*i] == 39)
			return(argv[*i]);
		*i += 1;
	}
	return(0);
}

int red_error(int *i, int *j, char *argv)
{
	int error;

	error = 0;
	char c1 = '>';
	char c2 = '<';
	while(argv[*i] == c1 || argv[*i] == c2)
	{
		*i += 1;
		*j += 1;
		if((argv[*i] == c1 && argv[*i - 1] == c2) || \
			(argv[*i] == c2 && argv[*i - 1] == c1))
		 	error = 1;
	}
	if(!ft_isalnum(argv[*i]))
		error = 1;
	return(error);
	
}

int handle_redirections(char *argv, size_t *j)
{
	int count;

	count = 0;
	int i = *j ;
	while(argv[i])
	{
		if(argv[i] == '>')
		{
			if(red_error(&i, &count, argv) || count > 2)
				return(0);
		}
		count = 0;
		if(argv[i] == '<')
		{
			if(red_error(&i, &count, argv) == 1 || count > 2)
				return(0);
		}
		else
			i++;
	}
	return(1);
}

int	quotes(char *argv)
{
	size_t i;
	int count = 0;

	i = 0;
	size_t j = 0;
	while(argv[i])
	{	
		j = i;
		char c = quotes_exist(argv, &j);
		if(c)
		{
			j++;
			while(argv[j] && argv[j] != c)
			{
				if(argv[j] == c)
					count++;
				j++;
			}
			if( j == ft_strlen(argv) && !count)
			{
				write(1, "Error unclosed quotes\n", 23);
				return(0);
			}	
		}
		i = j + 1;
	}
	return(1);
}

int	handle_pipe(char *argv)
{
	int	i;

	i = 0;
	while(argv[i])
	{
		if(argv[i] == '|')
		{
			if((argv[i + 1] == '|' &&  argv[i - 1] == '|' )
				|| argv[i - 1] == '<')
			{
				printf("parse error near `|' \n");
				return(0);
			}
		}
		i++;
	}
	return(1);
}

int	handle_errors(char *argv)
{
	size_t i;
	int j;

	i = 0;
	j = 0;
	if(!quotes(argv))
		return(0);
	while(argv[i])
	{
		if(argv[i] == '"' || argv[i] == 39)
		{
			j = i + 1;
			while(argv[j] != argv[i])
				j++;
			i = j;
		}
		if (!handle_redirections(argv, &i))
		{
			write(1, "syntax error near unexpected token\n", 36);
			return(0);
		}
		i++;
	}
	if(!handle_pipe(argv))
		return(0);
	return(1);
}