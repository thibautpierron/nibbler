/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncursesetup.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 08:42:10 by fdexheim          #+#    #+#             */
/*   Updated: 2017/10/26 18:47:04 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ncursesetup.hpp"

//------------------------------------------------------------------------------
void				setup_ncurses_color_pairs(void)
{
	init_pair(10, COL_GREY, COL_BLACK);
	init_pair(11, COL_WHITE, COL_BLACK);
	init_pair(12, COL_RED, COL_BLACK);
	init_pair(13, COL_LIGHT_RED, COL_BLACK);
	init_pair(14, COL_GREEN, COL_BLACK);
	init_pair(15, COL_LIGHT_GREEN, COL_BLACK);
	init_pair(16, COL_BLUE, COL_BLACK);
	init_pair(17, COL_LIGHT_BLUE, COL_BLACK);
	init_pair(18, COL_YELLOW, COL_BLACK);
	init_pair(19, COL_LIGHT_YELLOW, COL_BLACK);
	init_pair(20, COL_TEAL, COL_BLACK);
	init_pair(21, COL_LIGHT_TEAL, COL_BLACK);
	init_pair(22, COL_PURPLE, COL_BLACK);
	init_pair(23, COL_LIGHT_PURPLE, COL_BLACK);
	init_pair(24, COL_ORANGE, COL_BLACK);
	init_pair(25, COL_LIGHT_ORANGE, COL_BLACK);
	init_pair(26, COL_BROWN, COL_BLACK);
	init_pair(27, COL_LIGHT_BROWN, COL_BLACK);
	init_pair(28, COL_BLACK, COL_BLACK);
	init_pair(29, COL_WHITE, COL_WHITE);
	init_pair(30, COL_GREY, COL_GREY);
	init_pair(31, COL_DARKBLUE, COL_BLACK);
	init_pair(32, COL_LIGHT_ORANGE, COL_ORANGE);
	init_pair(33, COL_ORANGE, COL_LIGHT_ORANGE);
	init_pair(34, COL_GREEN, COL_GREEN);
	init_pair(35, COL_RED, COL_RED);
	init_pair(36, COL_LIGHT_BROWN, COL_BROWN);
	init_pair(37, COL_GREEN, COL_GREEN);
	init_pair(38, COL_LIGHT_BLUE, COL_LIGHT_BLUE);
}

//------------------------------------------------------------------------------
void				setup_ncurses_colors(void)
{
	init_color(COL_GREY, 400, 400, 400);
	init_color(COL_WHITE, 800, 800, 800);
	init_color(COL_RED, 800, 300, 300);
	init_color(COL_LIGHT_RED, 1000, 150, 150);
	init_color(COL_GREEN, 300, 800, 300);
	init_color(COL_LIGHT_GREEN, 150, 1000, 150);
	init_color(COL_BLUE, 300, 300, 800);
	init_color(COL_LIGHT_BLUE, 150, 150, 1000);
	init_color(COL_YELLOW, 800, 800, 300);
	init_color(COL_LIGHT_YELLOW, 1000, 1000, 150);
	init_color(COL_TEAL, 300, 800, 800);
	init_color(COL_LIGHT_TEAL, 150, 1000, 1000);
	init_color(COL_PURPLE, 800, 300, 800);
	init_color(COL_LIGHT_PURPLE, 1000, 150, 1000);
	init_color(COL_ORANGE, 800, 500, 300);
	init_color(COL_LIGHT_ORANGE, 1000, 600, 150);
	init_color(COL_BROWN, 600, 390, 200);
	init_color(COL_LIGHT_BROWN, 900, 600, 300);
	init_color(COL_BLACK, 0, 0, 0);
	init_color(COL_DARKBLUE, 0, 200, 400);
}

void				closeNcurses(void)
{
	endwin();
	curs_set(1);
}
//------------------------------------------------------------------------------
void				setup_ncurses(void)
{
	initscr();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(0);
	start_color();

	setup_ncurses_colors();
	setup_ncurses_color_pairs();
}
