/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncursesetup.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 08:41:52 by fdexheim          #+#    #+#             */
/*   Updated: 2017/10/26 15:59:01 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSESETUP_H
# define NCURSESETUP_H

# define COL_GREY 10
# define COL_WHITE 11
# define COL_RED 12
# define COL_LIGHT_RED 13
# define COL_GREEN 14
# define COL_LIGHT_GREEN 15
# define COL_BLUE 16
# define COL_LIGHT_BLUE 17
# define COL_YELLOW 18
# define COL_LIGHT_YELLOW 19
# define COL_TEAL 20
# define COL_LIGHT_TEAL 21
# define COL_PURPLE 22
# define COL_LIGHT_PURPLE 23
# define COL_ORANGE 24
# define COL_LIGHT_ORANGE 25
# define COL_BROWN 26
# define COL_LIGHT_BROWN 27
# define COL_BLACK 28
# define COL_DARKBLUE 29

#include <ncurses.h>

void			setup_ncurses_color_pairs(void);
void			setup_ncurses_colors(void);
void			setup_ncurses_windows(void);
void			setup_ncurses(void);
void			closeNcurses(void);

#endif
