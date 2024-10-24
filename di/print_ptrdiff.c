/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_ptrdiff.c                                     :+:    :+:           */
/*                                                      +:+                   */
/*   By: mde-beer <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/22 16:52:40 by mde-beer       #+#    #+#                */
/*   Updated: 2024/10/22 16:52:47 by mde-beer       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

void	print_ptrdiff(t_printf_arg *argument, int *count, va_list *args)
{
	const ptrdiff_t	value = va_arg(*args, ptrdiff_t);
	const int		vallen = get_ptrdiff_len(value);


}
