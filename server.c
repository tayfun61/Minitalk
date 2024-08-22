/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:54 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/22 14:39:05 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *src)
{
	int		i;
	int		j;	
	char	*new_str;

	if (src == 0)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	new_str = (char *)malloc((i + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	j = 0;
	while (src[j] != '\0')
	{
		new_str[j] = src[j];
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	calculating_value(int nb, int power)
{
	int	value;

	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	else
	{
		value = nb * calculating_value(nb, power - 1);
		return (value);
	}
}

char	*value_to_string(char const *s1, char const letter)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (!word)
		return (NULL);
	while (s1[i])
		word[j++] = s1[i++];
	i = 0;
	word[j++] = letter;
	word[j] = 0;
	free((void *)(s1));
	return (word);
}

void	signal_handler(int signum)
{
	static int	counter = 0;
	static int	result = 0;
	static char	*final;

	if (!final)
		final = ft_strdup("");
	if (signum == SIGUSR1)
		result = result + 0;
	else if (signum == SIGUSR2)
		result = result + (1 * calculating_value(2, 7 - counter));
	counter++;
	if (counter == 8)
	{
		final = value_to_string(final, result);
		if (result == '\0')
		{
			printf("%s\n", final);
			final = NULL;
		}
		counter = 0;
		result = 0;
	}
}

int	main(void)
{
	struct sigaction	signal_received;

	printf("Server's PID: %d\n", getpid());
	printf("Please open another terminal-window\n");
	printf("The format for messaging: ./client <PID> <Message>\n"); 
	signal_received.sa_handler = signal_handler;
	signal_received.sa_flags = 0;
	sigaction(SIGUSR1, &signal_received, NULL);
	sigaction(SIGUSR2, &signal_received, NULL);
	while (1)
		usleep(40);
}
