/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_signed_char.c                                 :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:50:44 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:50:59 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */


void	print_signed_char(t_printf_arg *argument, int *count, va_list *args)
{
	const signed char	value = va_arg(*args, signed char);
	const int			vallen = get_signed_char_len(value);


}


