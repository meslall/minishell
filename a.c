#include"minishell.h"

int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;
	int	qout;
	int type;
    char temp;

	qout = type = 0;
	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			if(type != 0 && s[i] == temp)
				qout++;
			if(s[i] == '"' && type == 0)
				{
                    temp = s[i];
					qout++;
					type = 2;
				}
			else if(s[i] == 39 && type == 0)
				{
                    temp = s[i];
					qout++;
					type = 1;
				}
		}
		else if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c && (qout == 2 || qout == 0))
		{
			flag = 0;
			qout = 0;
		}
		i++;
	}
	return (count);
}

int main()
{
    char *s = "\'ls \" vszvz szdfdsf ffdasdfasdf dsfadsfasd\"-la\'ll  l";

    printf("%d",count_words(s,' '));
}