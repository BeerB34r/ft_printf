/* ************************************************************************** */
/*                                                                            */
/*                                                            ::::::::        */
/*   get_argument.c                                          :+:    :+:       */
/*                                                          +:+               */
/*   By: mde-beer <mde-beer@student.codam.nl>              +#+                */
/*                                                        +#+                 */
/*   Created: 2025/11/17 19:33:50 by mde-beer            #+#    #+#           */
/*   Updated: 2025/11/17 21:45:55 by mde-beer            ########   odam.nl   */
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

static
int
	add_flag(
enum e_printf_flags *flags,
char c
)
{
	if (c == '-')
		*flags |= MINUS;
	else if (c == '+')
		*flags |= PLUS;
	else if (c == ' ')
		*flags |= SPACE;
	else if (c == '#')
		*flags |= ALTERNATE;
	else
		*flags |= ZERO;
	return (0);
}

static
int
	add_length(
enum e_printf_length *length,
char c
)
{
	if (*length == NONE && c == 'h')
		*length = H;
	else if (*length == NONE && c == 'l')
		*length = L;
	else if (*length == NONE && c == 'j')
		*length = J;
	else if (*length == NONE && c == 'z')
		*length = Z;
	else if (*length == NONE && c == 't')
		*length = T;
	else if (*length == NONE && c == 'L')
		*length = LD;
	else if (*length == H && c == 'h')
		*length = HH;
	else if (*length == L && c == 'l')
		*length = LL;
	else
		return (1);
	return (0);
}

static
int
	handle_width(
struct s_printf_argument *arg,
char c
)
{
	arg->using_width = true;
	if (c == '*')
		arg->w_arg = true;
	else
		arg->width = (10 * arg->width) + (c - '0');
	return (0);
}

static
int
	handle_precision(
struct s_printf_argument *arg,
char c
)
{
	arg->using_precision = true;
	if (c == '*')
		arg->p_arg = true;
	else
		arg->precision = (10 * arg->precision) + (c - '0');
	return (0);
}

int
	add_to_argument(
struct s_printf_argument *arg,
enum e_get_specifier_state state,
char c
)
{
	if (state == FLAGS)
		return (add_flag(&arg->flags, c));
	else if (state == WIDTH)
		return (handle_width(arg, c));
	else if (state == PRECISION)
		return (handle_precision(arg, c));
	else if (state == LENGTH)
		return (add_length(&arg->length, c));
	return (1);
}
