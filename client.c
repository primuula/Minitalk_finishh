/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:10:07 by safamran          #+#    #+#             */
/*   Updated: 2025/03/21 18:54:17 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack = 0;

void	pause_after_recieve(int signal)
{
	if (signal == SIGUSR1)
		g_ack = 1;
}

void	push_char(char c, int pid)
{
	int	col;
	int	bits;

	col = 7;
	while (col >= 0)
	{
		g_ack = 0;
		bits = c & (1 << col);
		if (bits != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		col--;
		while (g_ack == 0)
		{
		}
	}
}

int	handle_error(void)
{
	ft_putstr("Argument Error\n");
	return (1);
}

int	main(int argc, char *argv[])
{
	int					pid;
	int					i;
	struct sigaction	sa;

	sa.sa_handler = pause_after_recieve;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
		handle_error();
	i = 0;
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		handle_error();
	while (argv[2][i] != '\0')
	{
		push_char(argv[2][i], pid);
		i++;
	}
	push_char('\0', pid);
	return (0);
}
