/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:34:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/17 09:43:17 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


handle_builtin_child(cmds, envp);
handle_builtin_parent(cmds);

/*Builtin	            Seul	                            Dans un pipe

cd	                    parent	                            enfant
export	                parent	                            enfant
unset	                parent	                            enfant
exit	                parent	                            enfant
echo	                enfant ou parent	                enfant
pwd	                    enfant ou parent	                enfant

1. echo
2. pwd
3. env
4. export
5. unset
6. cd
7. exit
*/
