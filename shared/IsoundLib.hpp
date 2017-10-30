/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsoundLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:50:41 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/30 17:00:44 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISOUNDLIB_HPP
# define ISOUNDLIB_HPP

# include <vector>
# include <deque>

class IsoundLib {
	public:
		virtual void			playSound(const char *file) = 0;
};

#endif