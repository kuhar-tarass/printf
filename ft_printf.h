/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:48:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/04/30 21:42:57 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct		l_key
{
	struct l_key	*next;
	
	char			typedata;
	size_t			field;
	size_t			precision;
	int				skip;
	char			space;
	char			zero;
	char			minus;
	char			plus;
	char			hash;
	char			sizex2;
	char			size;
	
}					t_key;

char				*ft_itoa_base(unsigned long int n, int base);
char				*ft_getcharW(wchar_t c);
char				*ft_getstrW(wchar_t const *s);

#endif