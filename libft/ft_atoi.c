/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 15:32:26 by aguiller          #+#    #+#             */
/*   Updated: 2019/09/20 11:31:50 by aguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int					i;
	long long	int		num;
	long long	int		spec;

	i = 0;
	spec = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		spec = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10;
		num = num + ((int)str[i] - '0');
		i++;
	}
	num = num * spec;
	return (num);
}
