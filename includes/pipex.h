/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:09:07 by aautin            #+#    #+#             */
/*   Updated: 2023/12/13 22:39:00 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/libft.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

// errors_mgmt.c
int			is_right_format(int argc);
int			is_right_content(char *argv[], char *env[]);

// parsing.c
char		*commands_paths(char *env[]);

// main.c
int			main(int argc, char *argv[], char *env[]);

#endif