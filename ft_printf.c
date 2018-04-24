/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/24 23:18:29 by tkuhar           ###   ########.fr       */
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

int arg_parse(char *str)
{	
	int i;
	int field;
	int precision;
	char size_spec;


	size_spec = 0;
	field = 0;
	precision = 0;
	i = 0;
	printf("%s\n", str);
	while((str[i] == ' ' || str[i] == '0' || str[i] == '#' || str[i] == '+' || str[i] == '-') && str[i] != '\0')
		i++;
	if (str[i])
	{
		while(str[i] >= '0' && str[i] <= '9')
			field = field * 10 + str[i++] - 48;
		if (str[i] == '.')
		{
			i++;
			while(str[i] >= '0' && str[i] <= '9')
				precision = precision*10 + str[i++] - 48;
		}
		if (str[i] == 'h' || str[i] == 'l' || str[i] == 'z' || str[i] == 'j')
		{
			size_spec = str[i];
			i++;
		}
		if (size_spec && str[i] == size_spec)
			i++;
		return (truflag(str[i]));
	}
	return (0);
}

int	ft_printf(char *str, ...)
{
	char *tmp;
	
	tmp  = str;
	while(*tmp)
	{
		if (*tmp == '%')
			;

	}
	return(0);
}

int main ()
{
//	int a = 2845;
	

	
	printf("%d\n", arg_parse("   # +-25.9ld"));
	//printf("|% d|\n", a);
	
}
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