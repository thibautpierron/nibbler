/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IsoundLib.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:50:41 by mchevall          #+#    #+#             */
/*   Updated: 2017/10/31 11:30:01 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISOUNDLIB_HPP
# define ISOUNDLIB_HPP

# include <vector>
# include <deque>
# include "soundConstants.hpp"

class IsoundLib {
	public:
		virtual void			playSound(SoundAction::Enum action) = 0;
};

#endif