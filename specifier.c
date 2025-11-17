/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   specifier.c                                             :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 18:11:38 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 22:22:30 by mde-beer            ########   odam.nl   */
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
bool
	check_invalid(
char specifier,
struct s_printf_argument format
)
{
	if (specifier != '%' && specifier != 'n')
		return (false);
	if (format.flags
		|| format.using_width || format.w_arg || format.width
		|| format.using_precision || format.p_arg || format.precision)
		return (true);
	if (specifier == '%' && format.length)
		return (true);
	return (false);
}

char
	*get_specifier(
const char *format,
struct s_printf_argument *arg
)
{
	const static char				specifiers[] = "%csdioxXufFeEaAgGnp";
	enum e_get_specifier_state		state;
	bool							could_be_asterisk;
	char							*current;

	bzero(arg, sizeof(struct s_printf_argument));
	current = NULL;
	state = FLAGS;
	could_be_asterisk = true;
	while (*format)
	{
		current = strchr(specifiers, *format);
		if (current)
			break ;
		if (handle_state(&state, &format, &could_be_asterisk, arg))
			return (NULL);
	}
	if (current)
		arg->invalid = check_invalid(*current, *arg);
	return (current);
}
