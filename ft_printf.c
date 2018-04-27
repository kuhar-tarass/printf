/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/27 19:32:54 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


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

t_key *arg_parse(char *str)
{
	int i;
	t_key *k;

	k = malloc(sizeof(t_key));
	k->next = 0;
	k->field = 0;
	k->precision = 0;
	k->size = 0;
	k->space = 0;
	k->zero = 0;
	k->plus = 0;
	k->minus = 0;
	k->hash = 0;
	i = 0;
	while(i++ >= 0)
		if (str[i] == ' ')
			k->space = 1;
		else if (str[i] == '0')
			k->zero = 1;
		else if (str[i] == '-')
			k->minus = 1;
		else if (str[i] == '+')
			k->plus = 1;
		else if (str[i] == '#')
			k->hash = 1;
		else
			break;
	if (str[i])
	{
		while(str[i] >= '0' && str[i] <= '9')
			k->field = k->field * 10 + str[i++] - 48;
		if (str[i] == '.')
			while(str[++i] >= '0' && str[i] <= '9')
				k->precision = k->precision * 10 + str[i++] - 48;
		if (str[i] == 'h' || str[i] == 'l' || str[i] == 'z' || str[i] == 'j')
			k->size = str[i++];
		if (k->size && str[i] == k->size)
			k->sizex2 = str[i++] ? 1 : 0;
		k->typedata = truflag(str[i]) ? str[i] : 0;
	}
	return (k->typedata ? k : 0);
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

int	ft_printf(char *str, ...)
{
	char	*tmp;
	t_key	*keys;

	tmp  = str;
	keys = 0;
	while(*tmp)
	{
		if (*tmp == '%')
			addback(&keys,arg_parse(tmp));
		tmp++;
	}
	t_key 	*tmp1;
	tmp1 = keys;
	return(0);
}

int main (int ac, char **av)
{
//	int a = 2845;
	

	
//	printf("%-15.5f\n", -i);
//	printf("%08.9d\n", 12345);
	//ft_printf(av[1]);
	unsigned char s[3];
	wchar_t value = 3002;
	printf("	%s\n	%s\n", ft_itoa_base((unsigned int)value, 2), ft_itoa_base((((unsigned int)value)<<26)>>26, 2));
	//printf("%015X\n", -i);

	//printf("|%S|\n", "qwertyu");
	
}

//	1110xxxx 10xxxxxx 10xxxxxx
//	11100001 10001110 10001000
//		255		142		136
//
//
//
//
//
//
//
//
//
//
//
//
//
//
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