/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 11:56:34 by tkuhar            #+#    #+#             */
/*   Updated: 2018/05/11 16:24:44 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	truflag(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' ||
		c == 'i' || c == 'o' || c == 'O' || c == 'u' || c == 'U' ||
		c == 'x' || c == 'X' || c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

char		*strinsert(char **dst, char *src, int index)
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

void		spaaacesorzeeeros(char **s, t_key *k)
{
	int		f;
	char	*buf;
	int		lens;

	lens = (int)ft_strlen(*s);
	f = (((WIDTH - lens) > 0) ? (WIDTH - lens) : 0);
	buf = ft_strnew(f + 1);
	buf = ft_memset(buf, (PREC == -1 && ZERO) ? '0' : ' ', f);
	if (CONV == 'x' || CONV == 'X' || CONV == 'p')
		*s = strinsert(s,buf, (HASH && ZERO) || (ZERO && CONV == 'p') ? 2 : 0);
	else if (CONV == 'o' || CONV == 'O')
		*s = strinsert(s,buf,HASH && ZERO ? 1 : 0);
	else if (CONV == 'd' || CONV == 'i')
		*s = strinsert(s, buf, (**s == ' ' || **s == '-' || **s == '+') && ZERO ? 1 : 0);
	else
		*s = strinsert(s, buf, 0);
	free (buf);
	return ;
}

void		left(char **s, t_key *k)
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

void		addzero(char **s, t_key *k)
{
	int		size;
	char	*zeros;

	size = PREC - (int)ft_strlen(*s);
	zeros = ft_strnew(size + 1);
	zeros = ft_memset(zeros, '0', size);
	*s = strinsert(s, zeros, 0);
	free(zeros);
}

int			print_cC(int wchr, t_key *k)
{
	char	*tmp;
	int		out;

	if (wchr == 0)
		WIDTH = WIDTH ? WIDTH - 1 : WIDTH;
	if (CONV == 'c')
	{
		tmp = ft_strnew(1);
		*tmp = wchr;
	}
	else if (!(tmp = (char *)ft_getcharW(wchr)))
		return (-1);
	if (WIDTH)
		spaaacesorzeeeros(&tmp, k);
	if (LEFT)
		left(&tmp, k);
	if (CONV == 'c' || wchr == 0)
		out = write(1, tmp, (ft_strlen(tmp) + (wchr ? 0 : 1)));
	else
		out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_ss(int *ws, t_key *k)
{
	char	*tmp;
	int		size;
	int		lens;
	char	*s;
	int		out;
	
	if (ws == 0)
		s = ft_strjoin(0, "(null)");
	else 
		s = CONV == 'S' || SMOD == 'l' ? (char *)ft_getstrw(ws) :
			ft_strjoin(0,(char *)ws);
	if (s == 0)
		return (-1);
	lens = (int)ft_strlen(s);
	size = lens;
	if (PREC >= 0)
		size = ((lens - PREC) >= 0) ? PREC : lens;
	tmp = ft_strsub(s, 0, size);
	spaaacesorzeeeros(&tmp,k);
	if (LEFT)
		left(&tmp,k);
	out = write(1, tmp, ft_strlen(tmp));
	free(s);
	free(tmp);
	return (out);
}

int			print_xo(unsigned long n, t_key *k)
{
	char	*tmp;
	int		fuckzero;
	int		out;

	tmp = ft_itoa_base(n, CONV == 'o' || CONV == 'O' ? 8 : 16);
	fuckzero = (int)ft_strlen(tmp);
	if (PREC > fuckzero)
		addzero(&tmp,k);
	if (!PREC  && !n)															// ! костиль
		*tmp = 0;
	if ((HASH && ((PREC <= fuckzero && n ) ||
		(!n && !PREC))) && (CONV == 'O' || CONV == 'o'))
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
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_di(long num, t_key *k)
{
	char	*tmp;
	char	sign;
	unsigned long n;
	int		out;

	n = num < 0 ? ~num + 1 : num;
	sign = num < 0 ? '-' : '+';
	SPACE = sign == '-' ? 0 : SPACE;
	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (!PREC && n == 0)
		*tmp = 0;
	if (SIGN || sign == '-')
		tmp = strinsert(&tmp, sign == '-' ? "-" : "+", 0);
	else if (SPACE == 1)
		tmp = strinsert(&tmp, " ", 0);
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

int			print_u(unsigned long n, t_key *k)
{
	char	*tmp;
	int		out;

	tmp = ft_itoa_base(n, 10);
	if (PREC > (int)ft_strlen(tmp))
		addzero(&tmp,k);
	if (!PREC && n == 0)
		*tmp = 0;
	if (WIDTH - (int)ft_strlen(tmp) > 0)
		spaaacesorzeeeros(&tmp,k);
	if (LEFT == 1)
		left(&tmp, k);
	out = write(1, tmp, ft_strlen(tmp));
	free(tmp);
	return (out);
}

static int	flag_parse(char *s, t_key *k)
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
	CONV = s[i + DSIZE];
	SKIP = i + DSIZE;
		return (k);
}

int		cCcall(va_list ap, t_key *k)
{
	int tmp;
	
	if ((SMOD == 'h' && DSIZE) && CONV == 'c')
			tmp = print_cC((char)va_arg(ap, int), k);
	else if (SMOD == 'h')
			tmp = print_cC((short)va_arg(ap, int ),k);
	else
			tmp = print_cC(CONV == '%' ? '%': va_arg(ap, int), k);
	return (tmp);
}

int		dDicall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'D')
		tmp = print_di(va_arg(ap, long ),k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_di((char)va_arg(ap, int),k);
	else if (SMOD == 'h')
		tmp = print_di((short)va_arg(ap, int ),k);
	else
		tmp = print_di((long)va_arg(ap, int ),k);
	return (tmp);
}

int		uUcall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'j' || CONV =='U' || SMOD == 'z')
		tmp = print_u((unsigned long)va_arg(ap, size_t),k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_u((char unsigned)va_arg(ap, unsigned),k);
	else if (SMOD == 'h')
		tmp = print_u((short unsigned)va_arg(ap, unsigned),k);
	else
		tmp = print_u((unsigned)va_arg(ap, size_t),k);
	return (tmp);
}

int		xopcall(va_list ap, t_key *k)
{
	int	tmp;

	if (SMOD == 'l' || SMOD == 'z' || SMOD == 'j' || CONV == 'O' || CONV == 'p')
		tmp = print_xo(va_arg(ap, size_t),k);
	else if (SMOD == 'h' && DSIZE)
		tmp = print_xo((unsigned char)va_arg(ap, size_t),k);
	else if (SMOD == 'h')
		tmp = print_xo((unsigned short)va_arg(ap, size_t),k);
	else
		tmp = print_xo((unsigned long)va_arg(ap, unsigned int),k);
	return (tmp);
}


static int	outstring(va_list ap, t_key *k)
{
	int tmp;

	tmp = 0;
	if (CONV == 'S' || CONV == 's')
		tmp = print_ss(va_arg(ap, int *), k);
	else if (CONV == 'c' || CONV == 'C' || CONV == '%')
		tmp = cCcall(ap, k);
	else if (CONV == 'x' || CONV == 'X' ||
		CONV == 'p' || CONV == 'o' || CONV == 'O')
		tmp = xopcall(ap, k);
	else if (CONV == 'i' || CONV == 'd' || CONV == 'D')
		tmp = dDicall(ap, k);
	else if (CONV == 'u' || CONV == 'U')
		tmp = uUcall(ap, k);
	return (tmp);
}





int		ft_printf(char *s, ...)
{
	va_list			ap;
	t_key			*k;
	int				tmp;
	int				i;
	char			*symb;
	char			other;
	int				count;

	va_start(ap, s);
	count = 0;
	while (1)
	{
		symb = ft_strchr(s, '%');
		if (!symb)
			break;
		i = symb - s;
		write(1, s, i);
		k = arg_parse(&s[i]);
		count += i;
		s += i + SKIP + 1;
		if (!truflag(CONV))
		{
			other = CONV;
			CONV = 'c';
			tmp = print_cC(other, k);
		}
		else
			tmp = outstring(ap, k);
		count += tmp;
		free (k);
		if (tmp < 0)
			break;
	}
	va_end(ap);
	if (tmp == -1)
		return (-1);
	i = ft_strlen((char*)s);
	count += i;
	write(1, s, i);
	return (count);
}