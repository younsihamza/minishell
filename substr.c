#include "header.h"

char *ft_type(char *str)
{
    //puts("here");
    if(strcmp(str, "|") == 0)
        return ("OP_PIPE");
    else if(strcmp(str, "||") == 0)
        return ("OP_OR");
    else if(strcmp(str, "&&") == 0)
        return ("OP_AND");
    else if(strcmp(str, ";") == 0)
        return("OP_SMC");
    else if((strcmp(str, ">") == 0) || (strcmp(str, "<") == 0) || (strcmp(str,">>") == 0) || (strcmp(str, "<<") == 0))
        return ("OP_RD");
    else 
        return ("OP_WR");
}

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	i;
	void	*p;

	i = 0;
	p = malloc(size * nitems);
	if (!p)
		return (NULL);
	while (i < nitems * size)
	{
		*(char *)(p + i) = '\0';
		i++;
	}
	return (p);
}

static int	sizeallocate(int lenstr, int start, int size)
{
	int	a;

	a = 0;
	if (lenstr > size)
		a = size;
	else
		a = lenstr - start;
	return (a);
}


size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	int		size;

	arr = NULL;
	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		arr = (char *)(ft_calloc(sizeof(char), 1));
		return (arr);
	}
	size = sizeallocate(ft_strlen(s), start, len);
	arr = (char *)(ft_calloc(sizeof(char), (size + 1)));
	if (!arr)
		return (NULL);
	while (size--)
	{
		*(arr + i) = *(s + start + i);
		i++;
	}
	return (arr);
}