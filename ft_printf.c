/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/05 21:18:37 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int count;
static int		truflag(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
		c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
		c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

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

void	spaaacesorzeeeros(char **s, t_key *k)
{
	int		f;
	char	*buf;
	int		lens;

	lens = (int)ft_strlen(*s);
	f = (((WIDTH - lens) > 0) ? (WIDTH - lens) : 0);
	buf = ft_strnew(f + 1);
	buf = ft_memset(buf, (PREC == -1 && ZERO) ? '0' : ' ', f);
	if (CONV == 'x' || CONV == 'X' || CONV == 'p')
		*s = strinsert(s,buf, (HASH && ZERO) ? 2 : 0);
	else if (CONV == 'o' || CONV == 'O')
		*s = strinsert(s,buf,HASH && ZERO ? 1 : 0);
	else if (CONV == 'd' || CONV == 'i')
		*s = strinsert(s, buf, (**s == ' ' || **s == '-' || **s == '+') && ZERO ? 1 : 0);
	else
		*s = strinsert(s, buf, 0);
	free (buf);
	return ;
}

void	left(char **s, t_key *k)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while ((*s)[i] == ' ')
		i++;
	if (SPACE == 1 && i && SIGN == 0 && CONV != '%')
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

	size = PREC - (int)ft_strlen(*s);
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
	if (c == 0)
	{
		WIDTH = WIDTH ? WIDTH - 1 : WIDTH;
		count++;
	}
	tmp = (char *)ft_getcharW(c);
	if (WIDTH)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT)
		left(&tmp, k);
	return(tmp);
}

// ?Was merged
/* 
char	*print_s(char *s, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;

	
	lens = (int)ft_strlen(s);
	size = lens;
	if (PREC >= 0)
		size = ((lens - PREC) >= 0) ? PREC : lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp,k);
	if (LEFT)
		left(&tmp,k);
	return (tmp);
}
*/
char	*print_S(int *ws, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;
	char	*s;
	
	if (ws == 0)
		s = ft_strjoin(0, "(null)");
	else 
		s = CONV == 'S' || SMOD == 'l' ? (char *)ft_getstrW(ws) : ft_strjoin(0,(char *)ws);
	lens = (int)ft_strlen(s);
	size = lens;
	if (PREC >= 0 /*&& CONV == 's'*/)
		size = ((lens - PREC) >= 0) ? PREC : lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp,k);
	if (LEFT)
		left(&tmp,k);
	free(s);
	return (tmp);
}

// ? Was merged with print_x/ print_o
// !
// !
//  //Fucking zeros
// ? DONE
// !
char	*print_xo(unsigned long n, t_key *k)
{
	char	*tmp;
	int		fuckzero;

	tmp = ft_itoa_base(n, CONV == 'o' || CONV == 'O' ? 8 : 16);
	fuckzero = (int)ft_strlen(tmp);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (!PREC  && !n)															// ! костиль
		*tmp = 0;
	if ((HASH && ((PREC <= fuckzero && n ) || (!n && !PREC))) && (CONV == 'O' || CONV == 'o'))
		tmp = strinsert(&tmp,"0",0);
	if ((HASH && n && CONV != 'O' && CONV != 'o') || CONV == 'p')
		tmp = strinsert(&tmp,"0x",0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	fuckzero = -1;
	while(tmp[++fuckzero] && CONV == 'X')
		tmp[fuckzero] = ft_toupper(tmp[fuckzero]);
	return (tmp);
}
/*
char	*print_o(unsigned long n, t_key *k)
{
	char	*tmp;
	char	*tmpzero;
	int		fuckzero;

	tmp = ft_itoa_base(n, 8);
	fuckzero = (int)ft_strlen(tmp);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (HASH == 1 && PREC <= fuckzero)
		tmp = strinsert(&tmp,"0",0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	return (tmp);
}
*/
// !
// !
// !
char	*print_di(long num, t_key *k)
{
	char	*tmp;
	char	sign;
	unsigned long n;

	n = num < 0 ? ~num + 1 : num;
	sign = num < 0 ? '-' : '+';
	SPACE = sign == '-' ? 0 : SPACE;
	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (!PREC && n == 0)														// ! костиль
		*tmp = 0;
	if (SIGN || sign == '-')
		tmp = strinsert(&tmp, sign == '-' ? "-" : "+", 0);
	else if (SPACE == 1)
		tmp = strinsert(&tmp, " ", 0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	return (tmp);
}
// !
// !
// ! reWRITE THIS PICE of SHIT
// ! need to BE MERGED
// !
// !
// !
char	*print_u(unsigned long n, t_key *k)
{
	char	*tmp;

	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (!PREC && n == 0)														// ! костиль
	*tmp = 0;
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	return (tmp);
}
// !
// !
// !
static int		flag_parse(char *s, t_key *k)
{
	int	i;

	SPACE = 0;
	ZERO = 0;
	LEFT = 0;
	SIGN = 0;
	HASH = 0;
	i = 0;
	while(s[++i] == 32 || s[i] == 48 || s[i] == 45 || s[i] == 43 || s[i] == 35)
	{
		SPACE = SPACE || s[i] == ' ' ? 1 : 0;
		LEFT = LEFT || s[i] == '-' ? 1 : 0;
		ZERO = (ZERO || s[i] == '0') && !LEFT ? 1 : 0;
		SIGN = SIGN || s[i] == '+' ? 1 : 0;
		HASH = HASH || s[i] == '#' ? 1 : 0;
	}
	return (i);
}

static t_key	*arg_parse(char *s)
{
	int i;
	t_key *k;

	k = malloc(sizeof(t_key));
	WIDTH = 0;
	PREC = -1;
	SMOD = 0;
	i = flag_parse(s,k);
	while(s[i] >= '0' && s[i] <= '9')
		WIDTH = WIDTH * 10 + s[i++] - 48;
	if (s[i] == '.' && !(PREC = 0))
		while(s[++i] >= '0' && s[i] <= '9')
			PREC = PREC * 10 + s[i] - 48;
	if (s[i] == 'h' || s[i] == 'l' || s[i] == 'z' || s[i] == 'j')
		SMOD = s[i++];
	DSIZE = (SMOD && s[i] == SMOD) ? 1 : 0;
	CONV = truflag(s[i + DSIZE]) ? s[i + DSIZE] : 0;
	SKIP = i + DSIZE;
	if (CONV != 0)
		return (k);
	free (k);
	return (0);
}

/*
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
*/

static unsigned char	*outstring(va_list ap, t_key *k)
{
	char *tmp;
	
	tmp = 0;
	if (CONV == 'S' || CONV == 's')
		tmp = print_S(va_arg(ap, int *), k);
	else if (CONV == 'c' || CONV == 'C' || CONV == '%')
	{
		
		if (SMOD == 'h' && DSIZE)
			tmp = print_c(CONV == '%' ? '%': (char)va_arg(ap, int), k);
		else if (SMOD == 'h')
			tmp = print_c((short)va_arg(ap, int ),k);
		else 
			tmp = print_c(CONV == '%' ? '%': va_arg(ap, int), k);
	}
	else if (CONV == 'x' || CONV == 'X' || CONV == 'p' || CONV == 'o' || CONV == 'O')
	{
		if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'O')
			tmp = print_xo(va_arg(ap, unsigned long),k);
		else if (SMOD == 'h' && DSIZE)
			tmp = print_xo((unsigned char)va_arg(ap, unsigned int),k);
		else if (SMOD == 'h')
			tmp = print_xo((unsigned short)va_arg(ap, unsigned int),k);
		else
			tmp = print_xo((unsigned long)va_arg(ap, unsigned int),k);
	}
	else if (CONV == 'i' || CONV == 'd' || CONV == 'D')
	{
		if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'D')
			tmp = print_di(va_arg(ap, long ),k);
		else if (SMOD == 'h' && DSIZE)
			tmp = print_di((char)va_arg(ap, int),k);
		else if (SMOD == 'h')
			tmp = print_di((short)va_arg(ap, int ),k);
		else
			tmp = print_di((long)va_arg(ap, int ),k);
	}
	else if (CONV == 'u' || CONV == 'U')
	{
		if (SMOD == 'l' || SMOD == 'j' || CONV =='U' || SMOD == 'z')
			tmp = print_u((unsigned long)va_arg(ap, unsigned long),k);
		else
			tmp = print_u((unsigned)va_arg(ap, unsigned),k);
	}
	return ((unsigned char *)tmp);
}
int		ft_printf(char *s, ...)
{
	va_list			ap;
	t_key			*k;
	unsigned char	*tmp;
	int				i;
	char			*symb;
	char			*start;

	va_start(ap, s);
	count = 0;
	start = s;
	while (1)
	{
		symb = ft_strchr(s, '%');
		if (!symb)
			break;
		i = symb - s;
		write(1, s, i);
		k = arg_parse(&s[i]);
		count += i;
		if (k == 0)
			return (-1);
		s = s + i + SKIP + 1;
		if (!(tmp = outstring(ap, k)))
			break;
		i = ft_strlen((char*)tmp);
		count += i;
		write(1, tmp, i);
		free (tmp);
		free (k);
	}
	va_end(ap);
	i = ft_strlen((char*)s);
	count += i;
	write(1, s, i);
	return (count);
}

/*

int		ft_printf2(char *s, ...)
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
		if (tmpkeys->typedata == 'S' || tmpkeys->typedata == 's')
			tm2 = (unsigned char*)print_S(va_arg(ap, int *), tmpkeys);
		else if (tmpkeys->typedata == 'c' || tmpkeys->typedata == 'C')
			tm2 = (unsigned char*)print_c(va_arg(ap, int),tmpkeys);
		else if (tmpkeys->typedata == 'x' || tmpkeys->typedata == 'X' || tmpkeys->typedata == 'p' || tmpkeys->typedata == 'o' || tmpkeys->typedata == 'O')
			tm2 = (unsigned char *)print_xo(va_arg(ap, unsigned long),tmpkeys);
		else if (tmpkeys->typedata == 'i' || tmpkeys->typedata == 'd')
		{
			if (tmpkeys->size == 'l')
				tm2 = (unsigned char *)print_di(va_arg(ap, long ),tmpkeys);
			else 
				tm2 = (unsigned char *)print_di((long)va_arg(ap, int ),tmpkeys);
		}
		else if (tmpkeys->typedata == 'u')
				tm2 = (unsigned char *)print_u((long)va_arg(ap, int ),tmpkeys);
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
*/
