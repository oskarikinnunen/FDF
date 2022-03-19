/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_errors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okinnune <okinnune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:14:24 by okinnune          #+#    #+#             */
/*   Updated: 2022/03/19 20:44:11 by okinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_ERRORS_H
# define FDF_ERRORS_H

void	error_exit_free_map(char *str, t_map *map);
void	error_exit(char *str);
#endif