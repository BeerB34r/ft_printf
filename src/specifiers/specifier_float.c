/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   specifier_float.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/19 01:07:40 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/19 03:06:27 by mde-beer            ########   odam.nl   */
/*                                                                            */
/*   —————No norm compliance?——————                                           */
/*   ⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝                                           */
/*   ⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇                                           */
/*   ⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀                                           */
/*   ⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀⠀                                           */
/*   ⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           */
/*   ——————————————————————————————                                           */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "fa_c.h"
#include "_printf.h"

int
	iroundld(
long double n
)
{
	return ((int)(n + 0.5));
}

int
	iroundd(
double n
)
{
	return ((int)(n + 0.5));
}

t_fa_c
	*get_fractional_str_ld(
long double fractional,
int precision
)
{
	static const char	radix[] = "0123456789";
	t_fa_c				*out;
	char				*buf;
	long double			tmp;
	int					i;

	if (!precision)
		return (calloc_fa_c(0));
	buf = calloc(precision + 2, sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = '.';
	i = 0;
	while (i < precision - 1)
	{
		fractional = modfl(fractional * 10, &tmp);
		buf[++i] = radix[(int)tmp];
	}
	buf[++i] = radix[iroundld(fractional * 10)];
	out = fa_c_from_str(buf);
	free(buf);
	return (out);
}

t_fa_c
	*get_integral_str_ld(
long double integral,
struct s_printf_argument *format
)
{
	static const char	radix[] = "0123456789";
	static const int	base = 10;
	char				buf[100];
	int					index;
	int					sign;

	sign = 1;
	if (integral < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	buf[99] = 0;
	buf[98] = radix[((int)integral % base) * sign];
	index = 97;
	while ((int)integral / 10)
	{
		integral /= 10;
		buf[index--] = radix[((int)integral % base) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*float_helper_long_double(
long double n,
struct s_printf_argument *format
)
{
	long double	integral;
	t_fa_c		*fractional_str;
	t_fa_c		*integral_str;
	t_fa_c		*out;

	if (isnan(n))
		return (fa_c_from_str("nan"));
	else if (isinf(n))
		return (fa_c_from_str("inf"));
	else if (n == 0)
		format->null = true;
	else if (!format->precision)
		return (get_integral_str_ld((long double)iroundld(n), format));
	out = NULL;
	fractional_str = get_fractional_str_ld(modfl(n, &integral),
			format->precision);
	integral_str = get_integral_str_ld(integral, format);
	if (integral_str && fractional_str)
		out = join_fa_c(integral_str, fractional_str);
	free(integral_str);
	free(fractional_str);
	return (out);
}

t_fa_c
	*get_fractional_str_d(
double fractional,
int precision
)
{
	static const char	radix[] = "0123456789";
	t_fa_c				*out;
	char				*buf;
	double				tmp;
	int					i;

	if (!precision)
		return (calloc_fa_c(0));
	buf = calloc(precision + 2, sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = '.';
	i = 0;
	while (i < precision - 1)
	{
		fractional = modf(fractional * 10, &tmp);
		buf[++i] = radix[(int)tmp];
	}
	buf[++i] = radix[iroundd(fractional * 10)];
	out = fa_c_from_str(buf);
	free(buf);
	return (out);
}

t_fa_c
	*get_integral_str_d(
double integral,
struct s_printf_argument *format
)
{
	static const char	radix[] = "0123456789";
	static const int	base = 10;
	char				buf[100];
	int					index;
	int					sign;

	sign = 1;
	if (integral < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	buf[99] = 0;
	buf[98] = radix[((int)integral % base) * sign];
	index = 97;
	while ((int)integral / 10)
	{
		integral /= 10;
		buf[index--] = radix[((int)integral % base) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*float_helper_double(
double n,
struct s_printf_argument *format
)
{
	double	integral;
	t_fa_c	*fractional_str;
	t_fa_c	*integral_str;
	t_fa_c	*out;

	if (isnan(n))
		return (fa_c_from_str("nan"));
	else if (isinf(n))
		return (fa_c_from_str("inf"));
	else if (n == 0)
		format->null = true;
	else if (!format->precision)
		return (get_integral_str_d((float)iroundd(n), format));
	out = NULL;
	fractional_str = get_fractional_str_d(modf(n, &integral),
			format->precision);
	integral_str = get_integral_str_d(integral, format);
	if (integral_str && fractional_str)
		out = join_fa_c(integral_str, fractional_str);
	free(integral_str);
	free(fractional_str);
	return (out);
}

t_fa_c
	*specifier_float(
va_list arg,
unsigned int current_len,
struct s_printf_argument *format
)
{
	(void)current_len;
	if (format->length != NONE && format->length != L && format->length != LD)
		return (NULL);
	else if (!format->using_precision)
		format->precision = 6;
	if (format->length == LD)
		return (float_helper_long_double(va_arg(arg, long double), format));
	else
		return (float_helper_double(va_arg(arg, double), format));
}
