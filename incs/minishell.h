/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felayan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:45:25 by felayan           #+#    #+#             */
/*   Updated: 2025/07/01 20:45:48 by felayan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>	//readline funcs
#include <readline/history.h>	//history funcs
#include <unistd.h>	// a lot of unix funcs
#include <stdlib.h>	// malloc, free
#include <stdio.h>	// printf
#include <sys/wait.h>	// wait, waitpid
#include <signal.h>	// signal handling
#include <fcntl.h>	//	open
#include <errno.h>	// error status
#include "libft.h"	// libft

#endif
