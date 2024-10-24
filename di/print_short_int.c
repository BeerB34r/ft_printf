/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_short_int.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:51:05 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:51:26 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_short_int(t_printf_arg *argument, int *count, va_list *args)
{
	const short int	value = va_arg(*args, short int);
	const int		vallen = get_short_int_len(value);


}


