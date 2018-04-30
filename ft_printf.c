/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/30 21:49:59 by tkuhar           ###   ########.fr       */
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

int print_c(int c, t_key *k)
{
	int	space;

	if (k->typedata == 'c')
	{
		if (k->field > 1)
		{
			space = k->field - 1;
			while 
		}
	}
	if (k->typedata == 'C')
}
void	print_s(char *s, t_key *k)
{
	int		i;
	int		space;

	if (k->precision == 0)
		return (0);
	i = ft_strlen(s);
	space = k->field - i > 0 ? k->field - i	: 0;
	while(space--)
		write(1, " ", 1);
	if (k->precision >= 0 && k->precision < i)
		write(1, s, k->precision);
	else
		write(1, s, i);
}

t_key *arg_parse(char *s)
{
	int i;
	t_key *k;

	k = malloc(sizeof(t_key));
	k->next = 0;
	k->field = 0;
	k->precision = -1;
	k->size = 0;
	i = 0;
	while(s[++i] == 32 || s[i] == 48 || s[i] == 45 || s[i] == 43 || s[i] == 35)
	{
		k->space = k->space || s[i] == ' ' ? 1 : 0;
		k->zero = k->zero || s[i] == '0' ? 1 : 0;
		k->minus = k->minus || s[i] == '-' ? 1 : 0;
		k->plus = k->plus || s[i] == '+' ? 1 : 0;
		k->hash = k->hash || s[i] == '#' ? 1 : 0;
	}
	if (s[i])
	{
		while(s[i] >= '0' && s[i] <= '9')
			k->field = k->field * 10 + s[i++] - 48;
		if (s[i] == '.')
		{
			k->precision = 0;
			while(s[++i] >= '0' && s[i] <= '9')
				k->precision = k->precision * 10 + s[i] - 48;
		}
		if (s[i] == 'h' || s[i] == 'l' || s[i] == 'z' || s[i] == 'j')
			k->size = s[i++];
		if (k->size && s[i] == k->size)
			k->sizex2 = s[i++] ? 1 : 0;
		k->typedata = truflag(s[i]) ? s[i] : 0;
	}
	if (k->typedata == 0)
	{
		free (k);
		return (0);
	}
	k->skip = i;
	return (k);
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
	t_key	*keys;
	t_key	*tmpkeys;
	va_list	ap;
	int		i;

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
	// /int size = lstsize(keys);
	tmp = s;
	while(i++ < lstsize(keys) && tmpkeys)
	{
		write(1, tmp, ft_strchr(tmp, '%') - tmp);
		tmp = ft_strchr(tmp,'%') + tmpkeys->skip + 1;
		if (tmpkeys->typedata == 's')
			print_s(va_arg(ap, char *), tmpkeys);
		if (tmpkeys->typedata == 'c')
			print_c(va_arg(ap, int), tmpkeys);
			
		else
			va_arg(ap, void *);
		tmpkeys = tmpkeys->next;
	}
	write(1,tmp, ft_strlen(tmp));
	t_key 	*tmp1;
	tmp1 = keys;
	return(0);
	va_end(ap);
}

int main (int ac, char **av)
{
	//ft_printf("%  s   hfjgh %s", "123", "456");
	//setlocale(LC_ALL, "");
	//printf("%9C|\n %d|\n %9c|\n", (wchar_t)945, 123456789, 'a');
	ft_printf("   |%.30s	%100.5s|", "123456789", "3456789");
}

//	1110xxxx 10xxxxxx 10xxxxxx
//	11100001 10001110 10001000
//		255		142		13 
/*
int sum(int, ...);

int main(void) {
   printf("Sum of 10, 20 and 30 = %d\n",  sum(3, 10, 20, 30) );
   printf("Sum of 4, 20, 25 and 30 = %d\n",  sum(4, 4, 20, 25, 30) );

   return 0;
}

int sum(int num_args, ...) {
   int val = 0;
   va_list ap;
   int i;

   va_start(ap, num_args);
   for(i = 0; i < num_args; i++) {
		val += va_arg(ap, int);
	}
	va_end(ap);

	return val;
}*/