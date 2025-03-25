/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safamran <safamran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:20:40 by safamran          #+#    #+#             */
/*   Updated: 2025/03/25 17:12:16 by safamran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// shakkuyaku love meallow
#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFER_SIZE 1000

// UTILS
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int nb);
int		ft_atoi(char *str);
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);

// serv & client
void	print_char(int signal, siginfo_t *info, void *context);
void	push_char(char c, int pid);

#endif
