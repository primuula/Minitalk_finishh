/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:10:18 by safamran          #+#    #+#             */
/*   Updated: 2025/03/25 16:51:44 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct s_build
{
	unsigned char	octet;
	int				col;
	unsigned char	*buffer;
	int				buffer_index;
	int				buffer_size;
	int				client_pid;
}					t_build;

t_build				g_lettre;

void	resize_buffer(void)
{
	unsigned char	*new_buff;
	int				new_size;

	new_size = g_lettre.buffer_size * 2;
	new_buff = ft_calloc(new_size, sizeof(unsigned char));
	if (!new_buff)
	{
		ft_putstr("Memory allocation error\n");
		exit(1);
	}
	ft_memcpy(new_buff, g_lettre.buffer, g_lettre.buffer_index);
	free(g_lettre.buffer);
	g_lettre.buffer = new_buff;
	g_lettre.buffer_size = new_size;
}

void	init_buffer(void)
{
	g_lettre.buffer_size = 10;
	g_lettre.buffer = ft_calloc(g_lettre.buffer_size, sizeof(unsigned char));
	if (!g_lettre.buffer)
	{
		ft_putstr("Memory allocation error\n");
		exit(1);
	}
	g_lettre.buffer_index = 0;
	g_lettre.octet = 0;
	g_lettre.col = 0;
}

void	sigaction_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	g_lettre.client_pid = info->si_pid;
	g_lettre.octet = g_lettre.octet << 1;
	if (signal == SIGUSR1)
		g_lettre.octet |= 1;
	g_lettre.col++;
	if (g_lettre.col == 8)
	{
		g_lettre.buffer[g_lettre.buffer_index++] = g_lettre.octet;
		if (g_lettre.buffer_index >= g_lettre.buffer_size)
			resize_buffer();
		if (g_lettre.octet == '\0')
		{
			g_lettre.buffer[g_lettre.buffer_index] = '\0';
			ft_putstr((char *)g_lettre.buffer);
			write(1, "\n", 1);
			free(g_lettre.buffer);
			init_buffer();
		}
		g_lettre.col = 0;
		g_lettre.octet = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	init_buffer();
	sa.sa_sigaction = sigaction_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_putstr("PID = ");
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

/*
#include "minitalk.h"

typedef struct s_build
{
	unsigned char	octet;
	int				col;
	unsigned char	buffer[100000];
	int				buffer_index;
	int				client_pid;
}					t_build;

t_build				g_lettre;

void	sigaction_handler(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	g_lettre.client_pid = info->si_pid;
	g_lettre.octet = g_lettre.octet << 1;
	if (signal == SIGUSR1)
		g_lettre.octet = g_lettre.octet | 1;
	g_lettre.col++;
	if (g_lettre.col == 8)
	{
		if (g_lettre.buffer_index < 99999)
		{
			g_lettre.buffer[g_lettre.buffer_index++] = g_lettre.octet;
			if (g_lettre.octet == '\n' || g_lettre.octet == '\0')
			{
				g_lettre.buffer[g_lettre.buffer_index] = '\0';
				ft_putstr((char *)g_lettre.buffer);
				write(1, "\n", 1);
				g_lettre.buffer_index = 0;
			}
		}
		g_lettre.col = 0;
		g_lettre.octet = 0;
		usleep(500);
	}
	kill(g_lettre.client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	g_lettre.octet = 0;
	g_lettre.col = 0;
	g_lettre.buffer_index = 0;
	g_lettre.client_pid = 0;
	sa.sa_sigaction = sigaction_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_putstr("PID = ");
	ft_putnbr(pid);
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
*/