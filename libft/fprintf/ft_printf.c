/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-c < jalves-c@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:22:43 by rphuyal           #+#    #+#             */
/*   Updated: 2024/05/16 23:51:27 by jalves-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*print_pointer(int fd, unsigned long long num, int *flength)
{
	char	*str;

	str = NULL;
	if (num == 0)
		*flength += ft_fputstr(fd, "(nil)");
	else
	{
		*flength += ft_fputstr(fd, "0x");
		str = ft_gethexstr(num, HEXMIN);
	}
	return (str);
}

static void	print_conversions(int fd, char c, va_list args_ptr, int *flength)
{
	char	*str;

	str = NULL;
	if (c == 'c')
		*flength += ft_fputcharprintf(fd, va_arg(args_ptr, int));
	else if (c == 's')
		*flength += ft_fputstr(fd, va_arg(args_ptr, char *));
	else if (c == 'p')
		str = print_pointer(fd, va_arg(args_ptr, unsigned long long), flength);
	else if (c == 'd' || c == 'i')
		str = ft_getintstr(va_arg(args_ptr, int));
	else if (c == 'u')
		str = ft_getintstr(va_arg(args_ptr, unsigned int));
	else if (c == 'x')
		str = ft_gethexstr(va_arg(args_ptr, unsigned int), HEXMIN);
	else if (c == 'X')
		str = ft_gethexstr(va_arg(args_ptr, unsigned int), HEXMAX);
	else if (c == '%')
		*flength += write(fd, "%", 1);
	if (str)
		*flength += ft_fputstr(fd, str);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	args_ptr;
	int		flenght;

	va_start(args_ptr, str);
	flenght = 0;
	while (*str)
	{
		if (*str == '%' && *(str++))
		{
			print_conversions(fd, *str, args_ptr, &flenght);
		}
		else
			flenght += ft_fputcharprintf(fd, *str);
		str++;
	}
	va_end(args_ptr);
	return (flenght);
}
