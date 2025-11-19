/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   specifier.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 18:11:38 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/18 20:28:42 by mde-beer            ########   odam.nl   */
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

#include "_printf.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

static
int
	handle_state_basic(
enum e_get_specifier_state *state,
const char **format,
struct s_printf_argument *arg
)
{
	const char *const	flag = strchr("-+ #0", **format);
	const char *const	length = strchr("hljztL", **format);

	if ((*state == FLAGS && flag) || (*state == LENGTH && length))
	{
		if (*state == FLAGS)
			(void)add_to_argument(arg, *state, *flag);
		else if (add_to_argument(arg, *state, *length))
			*state = MALFORMED;
		(*format)++;
		return (1);
	}
	else if (*state == PERIOD && **format == '.')
	{
		*state = PRECISION;
		(*format)++;
		return (1);
	}
	if (*state == FLAGS)
		*state = WIDTH;
	else if (*state == LENGTH)
		*state = MALFORMED;
	else
		*state = LENGTH;
	return (0);
}

static
int
	handle_state_store(
enum e_get_specifier_state *state,
const char **format,
bool *could_be_asterisk,
struct s_printf_argument *arg
)
{
	if (**format == '*' && *could_be_asterisk)
	{
		(void)add_to_argument(arg, *state, '*');
		if (*state == WIDTH)
			*state = PERIOD;
		else
			*state = LENGTH;
		(*format)++;
		return (1);
	}
	else if (*could_be_asterisk)
		*could_be_asterisk = false;
	if (isdigit(**format))
	{
		(void)add_to_argument(arg, *state, **format);
		(*format)++;
		return (1);
	}
	if (*state == WIDTH)
		*could_be_asterisk = true;
	if (*state == WIDTH)
		*state = PERIOD;
	else
		*state = LENGTH;
	return (0);
}

static int
	handle_state(
enum e_get_specifier_state *state,
const char **format,
bool *asterisk,
struct s_printf_argument *arg
)
{
	if (*state == FLAGS && handle_state_basic(state, format, arg))
		return (0);
	if (*state == WIDTH && handle_state_store(state, format, asterisk, arg))
		return (0);
	if (*state == PERIOD && handle_state_basic(state, format, arg))
		return (0);
	if (*state == PRECISION && handle_state_store(state, format, asterisk, arg))
		return (0);
	if (*state == LENGTH && handle_state_basic(state, format, arg))
		return (0);
	if (*state == MALFORMED)
		return (1);
	return (1);
}

static
void
	set_specifier_and_check_validity(
enum e_printf_specifier specifier,
struct s_printf_argument *format
)
{
	format->specifier = specifier;
	format->invalid = false;
	if (format->specifier != PERCENT && format->specifier != STORE)
		return ;
	if (format->flags
		|| format->using_width || format->w_arg || format->width
		|| format->using_precision || format->p_arg || format->precision)
		format->invalid = true;
	if (specifier == '%' && format->length)
		format->invalid = true;
}

char
	*parse_argument(
const char *format,
struct s_printf_argument *arg
)
{
	const static char						spec_char[] = "%csdioxXufFeEaAgGnp";
	const static enum e_printf_specifier	spec_enum[] = {
		PERCENT, CHARACTER, STRING, SIGNED_INTEGER, SIGNED_INTEGER, OCTAL,
		HEXADECIMAL, HEXADECIMAL, UNSIGNED_INTEGER, FLOAT, FLOAT,
		DECIMAL_EXPONENT, DECIMAL_EXPONENT, HEXADECIMAL_EXPONENT,
		HEXADECIMAL_EXPONENT, HEURISTIC_FLOAT, HEURISTIC_FLOAT, STORE, POINTER};
	enum e_get_specifier_state				state;
	bool									could_be_asterisk;
	char									*current;

	bzero(arg, sizeof(struct s_printf_argument));
	current = NULL;
	state = FLAGS;
	could_be_asterisk = true;
	while (*format)
	{
		current = strchr(spec_char, *format);
		if (current)
			break ;
		if (handle_state(&state, &format, &could_be_asterisk, arg))
			return (NULL);
	}
	if (current)
		set_specifier_and_check_validity(spec_enum[current - spec_char], arg);
	return (current);
}
