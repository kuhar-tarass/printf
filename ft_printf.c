/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/03 22:36:51 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>

int truflag(char c)
{
	char *s;

	s = malloc(sizeof(char)* 15);
	s = "sSpdDioOuUxXcC";
	while (*s)
		if (c == *s++)
			return (1);
	return (0);
}
/*
int	print_updiox(unsigned long int n, char sign, t_key *k)
{
	char	*b;
	int		base;
	size_t	size;
	char	*zero;
	char	*tmp;

	b = ft_itoa_base(n, base);
	size = ft_strlen(b);
	if (k->precision > b)
	{
		zero = ft_strnew(k->precision - size);
		ft_memset(zero, 48, k->precision - size);
		tmp = ft_strjoin(zero, b);
			return (0);
		free(b);
		free(zero);
		b = tmp;
	}
	size = ft_strlen(b);
	if (k->zero && !k->hash && k->field > size)
	{
		zero = ft_strnew(k->field - size);
		ft_memset(zero, 48, k->field - size);
		tmp = ft_strjoin(zero, b);
			return (0);
		free(b);
		free(zero);
		b = tmp;
	}
	if (base == 10 && sign)
		write(1, "-", 1);
	if (base == 16 && k->hash)
		write(1, "0x", 1);
	if (base == 8 && k->hash)
		write(1, "0", 1);
	write(1, b, ft_strlen(b));
}
*/


char	*strinsert(char **dst, char *src, int index)
{
	int		i;
	char	*tmp;
	int		dstl;

	dstl = ft_strlen(*dst);
	if (dst == 0 || !(tmp = ft_strnew(dstl + ft_strlen(src))) || index > dstl)
		return (0);
	i = -1;
	while (++i < index)
		tmp[i] = (*dst)[i];
	while (*src)
		tmp[i++] = *src++;
	while (index < dstl)
		tmp[i++] = (*dst)[index++];
	free(*dst);
	return (tmp);
}

// Need to rewrite
void	spaaacesorzeeeros(char **s, t_key *k)
{
	int		f;
	char	*buf;
	int		lens;

	lens = (int)ft_strlen(*s);
	f = (((k->field - lens) > 0) ? (k->field - lens) : 0);
	buf = ft_strnew(f + 1);
	if ((k->typedata == 'c' || k->typedata == 'C' || k->typedata == 's' || k->typedata == 'S' ) && f)
	{
		buf = ft_memset(buf, ' ', f);
		*s = strinsert(s, buf, 0);
		free (buf);
		return ;
	}
	if (k->typedata == 'x' || k->typedata == 'X' || k->typedata == 'p')
	{
		if (k->precision == -1 && k->zero == 1 && k->minus == 0)
		{
			buf = ft_memset(buf, '0', f);
			*s = strinsert(s,buf,k->hash ? 2 : 0);
			free (buf);
			return ;
		}
		buf = ft_memset(buf, ' ', f);
		*s = strinsert(s, buf, 0);
		free (buf);
		return ;
	}
	if (k->typedata == 'o' || k->typedata == 'O')
	{
		if (k->precision == -1 && k->zero == 1 && k->minus == 0)
		{
			buf = ft_memset(buf, '0', f);
			*s = strinsert(s,buf,k->hash ? 1 : 0);
			free (buf);
			return ;
		}
		buf = ft_memset(buf, ' ', f);
		*s = strinsert(s, buf, 0);
		free (buf);
		return ;
	}
	if (k->typedata == 'd' || k->typedata == 'i')
	{
		if (k->precision == -1 && k->zero == 1 && k->minus == 0)
		{
			buf = ft_memset(buf, '0', f);
			*s = strinsert(s, buf, **s == ' ' || **s == '-' || **s == '+' ? 1 : 0);
			free (buf);
			return ;
		}
		buf = ft_memset(buf, ' ', f);
		*s = strinsert(s, buf, 0);
		free (buf);
		return ;
	}
}

void	left(char **s, t_key *k)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while ((*s)[i] == ' ')
		i++;
	if ((int)k->space == 1)
		i--;
	tmp = ft_strsub(*s, i, ft_strlen(&(*s)[i]));
	tmp2 = ft_strsub(*s, 0, i);
	tmp = strinsert(&tmp, tmp2, ft_strlen(tmp));
	free(tmp2);
	free(*s);
	*s = tmp;
}

void	addzero(char **s, t_key *k)
{
	int		size;
	char	*zeros;
	char	*tmp;

	size = k->precision - (int)ft_strlen(*s);
	zeros = ft_strnew(size + 1);
	zeros = ft_memset(zeros, '0', size);
	*s = strinsert(s, zeros, 0);
	free(zeros);
}

char	*print_c(int wchr, t_key *k)
{
	char	*tmp;
	int 	c;

	c = wchr;
	tmp = (char *)ft_getcharW(c);
	spaaacesorzeeeros(&tmp, k);
	if (k->minus)
		left(&tmp, k);
	return(tmp);
}

char	*print_s(char *s, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;

	
	lens = (int)ft_strlen(s);
	size = lens;
	if (k->precision >= 0)
		size = ((lens - k->precision) >= 0) ? k->precision : lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp,k);
	if (k->minus == 1)
		left(&tmp,k);
	return (tmp);
}
// May be merged
char	*print_S(int *ws, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;
	char	*s;
	
	s = (char *)ft_getstrW(ws);
	lens = (int)ft_strlen(s);
	size = lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp,k);
	if (k->minus == 1)
		left(&tmp,k);
	free(s);
	return (tmp);
}

char	*print_x(unsigned long n, t_key *k)
{
	char	*tmp;
	char	*tmpzero;
	char	*counter;

	tmp = ft_itoa_base(n, 16);
	if (k->precision > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (k->hash == 1 || k->typedata == 'p')
		tmp = strinsert(&tmp,"0x",0);
	if (k->field - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (k->minus == 1)
		left(&tmp, k);
	counter = tmp;
	if (k->typedata == 'X')
		while(*counter)
		{
			*counter = ft_toupper(*counter);
			counter++;
		}
	return (tmp);
}
// May be merged with print_x/ print_o
char	*print_o(unsigned long n, t_key *k)
{
	char	*tmp;
	char	*tmpzero;
	int		fuckzero;

	tmp = ft_itoa_base(n, 8);
	fuckzero = (int)ft_strlen(tmp);
	if (k->precision > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (k->hash == 1 && k->precision <= fuckzero)
		tmp = strinsert(&tmp,"0",0);
	if (k->field - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (k->minus == 1)
		left(&tmp, k);
	return (tmp);
}

char	*print_di(unsigned long n, t_key *k)
{
	char	*tmp;
	char	sign;

	printf(">>%lu<<", (n));
	sign = ((unsigned long)1 << 63 & n) != 0 ? '-' : '+';
	tmp = ft_itoa_base((sign == '-' ? (~n + 1) : n), 10);
	if (k->precision > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (k->plus || sign == '-')
		tmp = strinsert(&tmp, sign == '-' ? "-" : "+", 0);
	else if (k->space == 1)
		tmp = strinsert(&tmp, " ", 0);
	if (k->field - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (k->minus == 1)
		left(&tmp, k);
	return (tmp);
}

int		flag_parse(char *s, t_key *k)
{
	int	i;

	k->space = 0;
	k->zero = 0;
	k->minus = 0;
	k->plus = 0;
	k->hash = 0;
	i = 0;
	while(s[++i] == 32 || s[i] == 48 || s[i] == 45 || s[i] == 43 || s[i] == 35)
	{
		k->space = k->space || s[i] == ' ' ? 1 : 0;
		k->zero = k->zero || s[i] == '0' ? 1 : 0;
		k->minus = k->minus || s[i] == '-' ? 1 : 0;
		k->plus = k->plus || s[i] == '+' ? 1 : 0;
		k->hash = k->hash || s[i] == '#' ? 1 : 0;
	}
	return (i);
}

t_key	*arg_parse(char *s)
{
	int i;
	t_key *k;

	k = malloc(sizeof(t_key));
	k->next = 0;
	k->field = 0;
	k->precision = -1;
	k->size = 0;
	i = flag_parse(s,k);
	if (s[i])
	{
		while(s[i] >= '0' && s[i] <= '9')
			k->field = k->field * 10 + s[i++] - 48;
		if (s[i] == '.' && !(k->precision = 0))
			while(s[++i] >= '0' && s[i] <= '9')
				k->precision = k->precision * 10 + s[i] - 48;
		if (s[i] == 'h' || s[i] == 'l' || s[i] == 'z' || s[i] == 'j')
			k->size = s[i++];
		k->sizex2 = (k->size && s[i++] == k->size) ? 1 : 0;
		k->typedata = truflag(s[i]) ? s[i] : 0;
	}
	k->skip = i;
	if (k->typedata != 0)
		return (k);
	free (k);
	return (0);
}

void	addback(t_key **keys, t_key *new)
{
	t_key *tmp;

	tmp = *keys;
	while(tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = new;
	else
		*keys = new;
}

int		lstsize(t_key *l)
{
	int i;

	i = 0;
	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}

int	ft_printf(char *s, ...)
{
	char	*tmp;
	unsigned char	*tm2 = 0;
	t_key	*keys;
	t_key	*tmpkeys;
	va_list	ap;
	int		i;
	int		lsts;

	va_start(ap, s);
	keys = 0;
	tmp = s;
	while(*tmp)
	{
		if (*tmp == '%')
			addback(&keys,arg_parse(tmp));
		tmp++;
	}
	i = 0;
	tmpkeys = keys;
	tmp = s;
	lsts = lstsize(keys);
	while(i++ < lsts && tmpkeys)
	{
		write(1, tmp, ft_strchr(tmp, '%') - tmp);
		tmp = ft_strchr(tmp,'%') + tmpkeys->skip + 1;
		if (tmpkeys->typedata == 's')
			tm2 = (unsigned char*)print_s(va_arg(ap, char *), tmpkeys);
		else if (tmpkeys->typedata == 'S')
			tm2 = (unsigned char*)print_S(va_arg(ap, int *), tmpkeys);
		else if (tmpkeys->typedata == 'c' || tmpkeys->typedata == 'C')
			tm2 = (unsigned char*)print_c(va_arg(ap, int),tmpkeys);
		else if (tmpkeys->typedata == 'x' || tmpkeys->typedata == 'X' || tmpkeys->typedata == 'p')
			tm2 = (unsigned char *)print_x(va_arg(ap, unsigned long),tmpkeys);
		else if (tmpkeys->typedata == 'o' || tmpkeys->typedata == 'O')
			tm2 = (unsigned char *)print_o(va_arg(ap, unsigned long),tmpkeys);
		else if (tmpkeys->typedata == 'i' || tmpkeys->typedata == 'd')
			tm2 = (unsigned char *)print_di(va_arg(ap, unsigned long),tmpkeys);
		else
			va_arg(ap, void *);
		tmpkeys = tmpkeys->next;
		if (tm2 != 0)
			write(1, tm2, ft_strlen((char*)tm2));
		free(tm2);
		tm2 = 0;
	}
	write(1,tmp, ft_strlen((char*)tmp));
	va_end(ap);
	return(0);
}

int main (int ac, char **av)
{
	setlocale(LC_ALL, "");
	int	or;
	int	ft;
	int	s[5] = {945,946,947,948,0};
	unsigned long lo = 30;
	or = printf		("or	§% -5d§|\n", -1);
	ft = ft_printf	("ft	§% -5d§|\n", -1);
	exit (0);
}

//	1110xxxx 10xxxxxx 10xxxxxx
//	11100001 10001110 10001000
//		255		142		13 
