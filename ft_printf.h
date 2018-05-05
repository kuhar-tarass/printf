/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:48:24 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/05 19:08:46 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONV k->typedata
# define WIDTH k->width
# define PREC k->precision
# define SPACE k->space
# define ZERO k->zero
# define LEFT k->minus
# define SIGN k->plus
# define HASH k->hash
# define SMOD k->size
# define DSIZE k->sizex2
# define SKIP k->skip
# include <stdio.h>
# include <stdarg.h>
# include <stdio.h>
# include "./libft/libft.h"

typedef struct		l_key
{	
	char			typedata;
	int				width;
	int				precision;
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
unsigned char		*ft_getcharW(wchar_t c);
char				*ft_getstrW(wchar_t const *s);

#endif
