/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   specifier_signed_integer.c                              :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/18 20:34:46 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/19 00:06:43 by mde-beer            ########   odam.nl   */
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

#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <sys/types.h>
#include <limits.h>
#include "fa_c.h"
#include "_printf.h"

t_fa_c
	*signed_int_helper_char(
char n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_short(
short n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_int(
int n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_long(
long n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_longlong(
long long n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_intmax_t(
intmax_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_ssize_t(
ssize_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*signed_int_helper_ptrdiff_t(
ptrdiff_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "0123456789";
	char				buf[100];
	int					sign;
	int					index;

	sign = 1;
	if (n < 0)
	{
		sign = -sign;
		format->sign = NEG_SIGN;
	}
	if (!n)
		format->null = true;
	buf[99] = 0;
	buf[98] = radix[(n % 10) * sign];
	index = 97;
	while (n / 10)
	{
		n /= 10;
		buf[index--] = radix[(n % 10) * sign];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*specifier_signed_integer(
va_list arg,
unsigned int current_len,
struct s_printf_argument *format
)
{
	(void)current_len;
	if (format->length == HH)
		return (signed_int_helper_char((char)va_arg(arg, int), format));
	else if (format->length == H)
		return (signed_int_helper_short((short)va_arg(arg, int), format));
	else if (format->length == NONE)
		return (signed_int_helper_int(va_arg(arg, int), format));
	else if (format->length == L)
		return (signed_int_helper_long(va_arg(arg, long), format));
	else if (format->length == LL)
		return (signed_int_helper_longlong(va_arg(arg, long long), format));
	else if (format->length == J)
		return (signed_int_helper_intmax_t(va_arg(arg, intmax_t), format));
	else if (format->length == Z)
		return (signed_int_helper_ssize_t(va_arg(arg, ssize_t), format));
	else if (format->length == T)
		return (signed_int_helper_ptrdiff_t(va_arg(arg, ptrdiff_t), format));
	else
		return (NULL);
}
