/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   specifier_octal.c                                       :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/18 23:12:59 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/19 00:19:11 by mde-beer            ########   odam.nl   */
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

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <strings.h>
#include <sys/types.h>
#include <limits.h>
#include "fa_c.h"
#include "_printf.h"

t_fa_c
	*octal_helper_char(
unsigned char n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_short(
unsigned short n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_int(
unsigned int n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_long(
unsigned long n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_longlong(
unsigned long long n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_uintmax_t(
uintmax_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_size_t(
size_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

t_fa_c
	*octal_helper_ptrdiff(
uintmax_t n,
struct s_printf_argument *format
)
{
	const static char	radix[] = "01234567";
	char				buf[100];
	int					index;

	buf[99] = 0;
	buf[98] = radix[n % 8];
	index = 97;
	if (!n)
		format->null = true;
	while (n / 8)
	{
		n /= 8;
		buf[index--] = radix[n % 8];
	}
	return (fa_c_from_str(&buf[index + 1]));
}

/**
 * the specification states that the formatstring "%tu" should interpret the
 * given value as whatever the systems unsigned version of ptrdiff_t is.
 * this doesnt exist. so im taking the liberty of pretending that the ptrdiff_t
 * is unsigned (however that would work) by shoving the bits (unchanged) into a
 * uintmax_t. thats basically an unsigned version of the bits right... right???
 */
t_fa_c
	*specifier_octal(
va_list arg,
unsigned int current_len,
struct s_printf_argument *format
)
{
	ptrdiff_t	edge_case;

	(void)current_len;
	if (format->length == HH)
		return (octal_helper_char((u_char)va_arg(arg, u_int), format));
	else if (format->length == H)
		return (octal_helper_short((u_short)va_arg(arg, u_int), format));
	else if (format->length == NONE)
		return (octal_helper_int(va_arg(arg, u_int), format));
	else if (format->length == L)
		return (octal_helper_long(va_arg(arg, u_long), format));
	else if (format->length == LL)
		return (octal_helper_longlong(va_arg(arg, unsigned long long), format));
	else if (format->length == J)
		return (octal_helper_uintmax_t(va_arg(arg, uintmax_t), format));
	else if (format->length == Z)
		return (octal_helper_size_t(va_arg(arg, size_t), format));
	else if (format->length == T)
	{
		edge_case = va_arg(arg, ptrdiff_t);
		return (octal_helper_ptrdiff(*(uintmax_t *)&edge_case, format));
	}
	else
		return (NULL);
}
