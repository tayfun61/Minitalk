/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:51:24 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/22 14:39:05 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		if (str[i + 1] == '+' || str [i + 1] == '-')
			return (0);
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((result == 214748364) && (str[i] == '8') && (sign % 2 == 1))
			return (-2147483648);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	sending_signal(int pid, char *text)
{
	int	letter;
	int	i;

	letter = 0;
	while (text[letter])
	{
		i = 0;
		while (i < 8)
		{
			if (((unsigned char)(text[letter] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(text[letter] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(40);
			i++;
		}
		letter++; 
	}
	i = 0;
	while (i < 8)
	{
		kill(pid, SIGUSR1);
		usleep(40);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*text;
	int		pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		if (!pid || pid < 0)
		{
			printf("Error. Wrong server id.");
			return (0);
		}
		text = argv[2];
		if (text[0] == 0)
		{
			printf("No message");
			return (0);
		}
		sending_signal(pid, text);
	}
	else
		printf("Error. Required format: ./client <PID> <Text>");
	return (0);
}
