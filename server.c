/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:10:10 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/04/19 16:49:32 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signal)
{
	static int	bit_counter;
	static char	message;

	if (signal == SIGUSR1)
		message = (message << 1) | 0;
	else if (signal == SIGUSR2)
		message = (message << 1) | 1;
	else
		return ;
	bit_counter++;
	if (bit_counter == 8)
	{
		if (message == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", message);
		bit_counter = 0;
		message = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
