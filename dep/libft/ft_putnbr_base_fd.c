/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 01:37:40 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/31 05:41:35 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(long n, int base)
{
	if (n == 0)
		return (0);
	if (n < 0)
		return (get_len(-n, base) + 1);
	return (get_len(n / base, base) + 1);
}

static int	allocate(char **result, char **set, int base, int len)
{
	char	*full_set;

	full_set = "0123456789abcdefghijklmnopqrstuvwxyz";
	*result = malloc((len + 1) * sizeof(char));
	if (!(*result))
		return (1);
	*set = malloc((base + 1) * sizeof(char));
	if (!(*set))
	{
		free(*result);
		return (1);
	}
	(*set)[base] = '\0';
	while (base--)
		(*set)[base] = full_set[base];
	return (0);
}

static void	handle_negative(long *n, int *stop, char *result)
{
	result[0] = '-';
	(*stop)++;
	*n *= -1;
}

static int	putnbr_base(int fd, char *result)
{
	int	ret;

	ret = write(fd, result, ft_strlen(result));
	free(result);
	return (ret);
}

int	ft_putnbr_base_fd(long n, int base, int fd)
{
	char	*set;
	int		len;
	char	*result;
	int		stop;

	if (base < 2 || base > 36)
		return (-2);
	len = get_len(n, base);
	if (n == 0)
		len = 1;
	if (allocate(&result, &set, base, len))
		return (-3);
	result[len] = '\0';
	stop = 0;
	if (n < 0)
		handle_negative(&n, &stop, result);
	while (len-- > stop)
	{
		result[len] = *(set + (n % base));
		n /= base;
	}
	free(set);
	return (putnbr_base(fd, result));
}
