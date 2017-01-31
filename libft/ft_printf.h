/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 22:42:58 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/27 21:58:07 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

typedef struct	s_env
{
	va_list	arg;
	int		i;
	int		hash;
	int		zero;
	int		minus;
	int		plus;
	int		space;
	int		none;
	int		width;
	int		prec;
	int		hh;
	int		h;
	int		l;
	int		ll;
	int		j;
	int		z;
	int		ret;
	int		r;
}				t_env;

int				ft_printf(char *fmt, ...);
void			fillstr(char *str, t_env *env);
void			lcconv(t_env *env);
char			*sjfplus(char *s1, char *s2, t_env *env);
void			envreset(t_env *env);
void			setflags(char *fmt, t_env *env);
int				isflag(char c);
int				ft_abs(int n);
void			settype(char *fmt, t_env *env);
void			invtype(char c, t_env *env);
char			*sjoinfree(char *s1, char *s2);
char			*snjoinfree(char *s1, char *s2, size_t len);
char			*ft_lltoa_base(long long value, int base);
char			*ft_ulltoa_base(unsigned long long value, int base);
void			xconv(char type, t_env *env);
char			*xconvstd(unsigned long long x, t_env *env);
char			*xconvzero(unsigned long long x, t_env *env);
void			oconv(char type, t_env *env);
char			*oconvstd(unsigned long long o, t_env *env);
char			*oconvzero(unsigned long long o, t_env *env);
int				iswidth(char c);
void			setwidth(char *fmt, t_env *env);
void			setprec(char *fmt, t_env *env);
int				ismod(char c);
void			setmod(char *fmt, t_env *env);
void			slsconv(char type, t_env *env);
int				ishead(char c);
void			trimucs(char *str);
void			lsconv(t_env *env);
void			sconv(t_env *env);
char			**getunicode(char *bin);
char			*fillutf(char *utf, char *bin);
void			printuc(char **uc);
unsigned char	atocbin(char *str);
char			*ucstostr(wchar_t *ucs);
void			clcconv(char type, t_env *env);
void			cconv(t_env *env);
void			free2d(char **strs);
void			retcount(char **strs, t_env *env);
void			percentconv(t_env *env);
void			pconv(t_env *env);
void			uconv(char type, t_env *env);
char			*uconvstd(unsigned long long u, t_env *env);
char			*uconvzero(unsigned long long u, t_env *env);
void			dconv(char type, t_env *env);
char			*dconvstd(long long d, t_env *env);
char			*dconvzero(long long d, t_env *env);

#endif
