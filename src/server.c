/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhomem-d <dhomem-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:28:31 by dhomem-d          #+#    #+#             */
/*   Updated: 2022/06/08 17:51:50 by dhomem-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int sig, siginfo_t *siginfo, void *ignore)
{
	static char	letter;
	static int	bite;

	(void)ignore;
	if (sig == SIGUSR2)
		letter |= (1 << bite);
	bite++;
	if (bite == 8)
	{
		ft_printf("%c", letter);
		if (letter == '\0')
			kill(siginfo->si_pid, SIGUSR2);
		letter = 0;
		bite = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %i\n", (int)getpid());
	while (1)
		pause();
	return (0);
}
