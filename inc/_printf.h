/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   _printf.h                                               :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/15 20:07:26 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/18 20:24:09 by mde-beer            ########   odam.nl   */
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

/**	
 * Internal header for ft_printf(), ft_snprintf(), and ft_dprintf()
 */

#ifndef _PRINTF_H
# define _PRINTF_H

// Header inclusions
# include <stdarg.h>
# include <stdbool.h>
# include "fa_c.h"

// Type declarations
enum e_printf_specifier
{
	PERCENT,
	CHARACTER,
	STRING,
	SIGNED_INTEGER,
	OCTAL,
	HEXADECIMAL,
	UNSIGNED_INTEGER,
	FLOAT,
	DECIMAL_EXPONENT,
	HEXADECIMAL_EXPONENT,
	HEURISTIC_FLOAT,
	STORE,
	POINTER
};

enum e_get_specifier_state
{
	FLAGS,
	WIDTH,
	PERIOD,
	PRECISION,
	LENGTH,
	MALFORMED
};

enum e_printf_flags
{
	MINUS = 1 << 0,
	PLUS = 1 << 1,
	SPACE = 1 << 2, // IGNORED IF PLUS == TRUE
	ALTERNATE = 1 << 3,
	ZERO = 1 << 4,
};

enum e_printf_length
{
	NONE,
	HH,
	H,
	L,
	LL,
	J,
	Z,
	T,
	LD
};

enum e_printf_sign
{
	NO_SIGN,
	NEG_SIGN,
	POS_SIGN,
	SPC_SIGN
};

struct s_printf_argument
{
	enum e_printf_flags		flags;
	bool					using_width;
	bool					w_arg;
	int						width;
	bool					using_precision;
	bool					p_arg;
	int						precision;
	enum e_printf_length	length;
	enum e_printf_specifier	specifier;
	enum e_printf_sign		sign;
	bool					uppercase;
	bool					null;
	bool					invalid;
};
// Function prototypes
t_fa_c
	*handle_raw(
		const char **format
		);	// FILE: handle_raw.c
char
	*get_specifier(
		const char *format,
		struct s_printf_argument *arg
		);	// FILE: specifier.c
int	
	add_to_argument(
		struct s_printf_argument *arg,
		enum e_get_specifier_state state,
		char c
		);	// FILE: get_argument.c
t_fa_c
	*handle_format(
		const char **format,
		va_list args,
		unsigned int current_len
		);	// FILE: handle_format.c
int	
	handle_precision(
		t_fa_c **out,
		struct s_printf_argument format
		);	// FILE: handle_precision.c
int	
	handle_sign(
		t_fa_c **out,
		struct s_printf_argument format
		);	// FILE: handle_sign.c
int	
	handle_width(
		t_fa_c **out,
		struct s_printf_argument format
		);	// FILE: handle_width.c
//	//	Specifier functions
t_fa_c
	*specifier_percent(
		va_list args,
		unsigned int current_len,
		struct s_printf_argument *format
		);	// FILE: specifier_percent.c
t_fa_c
	*specifier_character(
		va_list args,
		unsigned int current_len,
		struct s_printf_argument *format
		);	// FILE: specifier_character.c
t_fa_c
	*specifier_string(
		va_list args,
		unsigned int current_len,
		struct s_printf_argument *format
		);	// FILE: specifier_string.c
t_fa_c
	*specifier_store(
		va_list args,
		unsigned int current_len,
		struct s_printf_argument *format
		);	//FILE: specifier_store.c
#endif // _PRINTF_H
