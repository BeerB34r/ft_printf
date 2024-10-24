/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_long_int.c                                    :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:51:27 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:51:42 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_long_int(t_printf_arg *argument, int *count, va_list *args)
{
	const long int	value = va_arg(*args, long int);
	const int		vallen = get_long_int_len(value);

}


