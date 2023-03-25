#include "minishell.h"

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

size_t	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_chr_index(char *str ,char a,int *len)
{
     int i ;
    i = 0;
    while(str[i])
    {
        if( str[i] == a)
            return(i);
		*len += 1;
        i++;
    }
    return(-1);
}
int ft_strchr(char *str ,char a)
{
    int i ;
    i = 0;
    while(str[i])
    {
        if( str[i] == a)
            return(1);
        i++;
    }
    return(0);
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

int ft_strcmp(char *str1 , char *str2)
{
	int i = 0;
	while(str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return(str1[i] - str2[i]);
}
char	*ft_substr(char const *s, size_t start, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	r;
	char	*p;

	j = 0 ;
	i = start ;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		p = ft_calloc(sizeof(char), 1);
		return (p);
	}
	if (ft_strlen(s + start) > len)
		r = len;
	else
		r = ft_strlen(s + start);
	p = ft_calloc(sizeof(char), r + 1);
	if (!p)
		return (NULL);
	while (j < r)
		*(p + j++) = *(s + i++);
	return (p);
}

int	ft_strncmp( const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*str11 ;
	unsigned char	*str22 ;

	str11 = (unsigned char *)str1 ;
	str22 = (unsigned char *)str2 ;
	i = 0;
	if (n == 0)
		return (0);
	while ((*(str11 + i) || *(str22 + i))
		&& *(str11 + i) == *(str22 + i) && i < n - 1)
		i++;
	return (*(str11 + i) - *(str22 + i));
}
char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*arr;
	char	*set1;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	str = (char *)s1;
	set1 = (char *)set;
	i = 0;
	j = ft_strlen(str) - 1;
	while (ft_strchr(set1, *(str + i)) != 0)
		i++;
	while (ft_strchr(set1, *(str + j)) != 0)
		j--;
	if (j < i)
		arr = ft_substr(str, i, (i - j + 1));
	else
		arr = ft_substr(str, i, (j - i + 1));
	return (arr);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	j = 0;
	i = 0;
	p = malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!p)
		return (NULL);
	while (*(s1 + j))
		*(p + i++) = *(s1 + j++);
	j = 0;
	while (*(s2 + j))
		*(p + i++) = *(s2 + j++);
	*(p + i) = '\0';
	return (p);
}