/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:47 by aautin            #+#    #+#             */
/*   Updated: 2024/01/11 18:12:24 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// define with ifndef and endif the .h

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft_extended.h"
# include <errno.h>
# include <sys/wait.h>

// utils.c

// pipex.c
int			main(int argc, char *argv[], char **envp);

#endif