/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   handle_sign.c                                           :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 22:30:24 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 22:31:18 by mde-beer            ########   odam.nl   */
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
#include <stdlib.h>
#include "fa_c.h"
#include "_printf.h"

static
int
	basic_sign(
t_fa_c **out,
struct s_printf_argument format
)
{
	static const char *const	negative = "-";
	static const char *const	positive = "+";
	static const char *const	space = " ";
	t_fa_c						*internal;
	t_fa_c						*temp;

	if (format.sign == NO_SIGN)
		return (0);
	else if (format.sign == NEG_SIGN)
		internal = fa_c_from_str(negative);
	else if (format.sign == POS_SIGN)
		internal = fa_c_from_str(positive);
	else
		internal = fa_c_from_str(space);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	temp = join_fa_c(internal, *out);
	free(internal);
	free(*out);
	*out = temp;
	return (!*out);
}

static
int
	octal_sign(
t_fa_c **out,
struct s_printf_argument format
)
{
	static const char *const	prefix = "0";
	t_fa_c						*internal;
	t_fa_c						*temp;

	if (!(format.flags & ALTERNATE))
		return (0);
	internal = fa_c_from_str(prefix);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	temp = join_fa_c(internal, *out);
	free(internal);
	free(*out);
	*out = temp;
	return (!*out);
}

static
int
	hex_sign(
t_fa_c **out,
struct s_printf_argument format
)
{
	static const char *const	prefix = "0x";
	t_fa_c						*internal;
	t_fa_c						*temp;

	if (!(format.flags & ALTERNATE))
		return (0);
	internal = fa_c_from_str(prefix);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	temp = join_fa_c(internal, *out);
	free(internal);
	free(*out);
	*out = temp;
	return (!*out);
}

static
int
	hex_float_sign(
t_fa_c **out,
struct s_printf_argument format
)
{
	static const char *const	prefix = "0x";
	static const char *const	min_prefix = "-0x";
	t_fa_c						*internal;
	t_fa_c						*temp;

	if (!(format.flags & ALTERNATE))
		internal = fa_c_from_str(prefix);
	else
		internal = fa_c_from_str(min_prefix);
	if (!internal)
	{
		free(*out);
		return (1);
	}
	temp = join_fa_c(internal, *out);
	free(internal);
	free(*out);
	*out = temp;
	return (!*out);
}

// As a reminder, the format specifiers enum is in the following order:
// PERCENT
// CHARACTER
// STRING
// SIGNED_INTEGER
// OCTAL
// HEXADECIMAL
// UNSIGNED_INTEGER
// FLOAT
// DECIMAL_EXPONENT
// HEXADECIMAL_EXPONENT
// HEURISTIC_FLOAT
// STORE
// POINTER

int
	handle_sign(
t_fa_c **out,
struct s_printf_argument format
)
{
	static int (*const	specifiers[])(t_fa_c **, struct s_printf_argument) = {
		NULL,
		NULL,
		NULL,
		basic_sign,
		octal_sign,
		hex_sign,
		NULL,
		basic_sign,
		basic_sign,
		hex_float_sign,
		NULL,
		NULL,
		hex_sign
	};

	if (specifiers[format.specifier])
		return (specifiers[format.specifier](out, format));
	return (0);
}
