/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:34:03 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/06/08 17:54:25 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	send_signal(int pid, char byte)
{
	int	bit_counter;

	bit_counter = 0;
	while (bit_counter < 8)
	{
		if (byte >> bit_counter & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(40);
		bit_counter++;
	}
}

void	signaler(int pid, char *string)
{
	int	counter;

	counter = 0;
	while (string[counter])
	{
		send_signal(pid, string[counter]);
		counter++;
	}
	send_signal(pid, 0);
}

void	exit_success(int sig)
{
	(void)sig;
	ft_printf("Message received\n");
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	signal(SIGUSR2, exit_success);
	if (argc != 3)
		exit(EXIT_FAILURE);
	signaler(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
