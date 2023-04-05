/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrgonza <adrgonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:06:52 by amejia            #+#    #+#             */
/*   Updated: 2023/03/15 00:24:27 by adrgonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_printf(const char *string, ...);
void	process_string(char *str, va_list va_ptr, int *nchar);
char	*tag_process(char *tag_pos, va_list va_ptr, int *nchar);
int		pseudolog10(int n);
int		pseudolog10_u(unsigned int n);
int		pseudologbase(long n, long base);
int		pseudologbase_u(unsigned long n, long base);
void	ft_putnbr_base_fd_u(unsigned int nbr, char *base, int fd);
void	ft_putnbr_base_fd_ul(unsigned long nbr, char *base, int fd);
void	ft_putnbr_base_fd(long nbr, char *base, int fd);
char	*ft_strchr(const char *s, int c);
void	ft_putnstr_fd(char *s, int fd, unsigned int n);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int nb, int fd);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, unsigned int len);
int		check_base(char *str);
void	tag_i(va_list va_ptr, int *nchar);
void	tag_u(va_list va_ptr, int *nchar);
void	tag_s(va_list va_ptr, int *nchar);
void	tag_c(va_list va_ptr, int *nchar);
void	tag_sym(int *nchar);
void	tag_p(va_list va_ptr, int *nchar);
void	tag_x(va_list va_ptr, int *nchar);
void	tag_ux(va_list va_ptr, int *nchar);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putunbr_fd(unsigned int nb, int fd);
char	*ft_min_str(char *s1, char *s2);

#endif
