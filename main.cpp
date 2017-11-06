/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/11/06 14:25:05 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

bool is_digits(const std::string &str) {
    return (str.find_first_not_of("0123456789") == std::string::npos);
}

static void     checkParameters(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "error: need 2 parameters, width & height" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!is_digits(av[1]))
    {
        std::cerr << "error: invalid parameters" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (!is_digits(av[2]))
    {
        std::cerr << "error: invalid parameters" << std::endl;
        exit(EXIT_FAILURE);
    }
    long int width = strtol(av[1], NULL, 0);
    long int height = strtol(av[2], NULL, 0);
    if (width == 0L || height == 0L) {
        std::cerr << "error: invalid parameters" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (width < 20 || height < 20) {
        std::cerr << "error: parameters minimum is 20" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (width > 50 || height > 50) {
        std::cerr << "error: parameters maximum is 50" << std::endl;
        exit(EXIT_FAILURE);
    }


}

int     main(int ac, char **av) {
    srand(time(NULL));
    checkParameters(ac, av);
    const char *libnames[4] = {"openglDL/OpenglDL.so", "nCursesDL/nCursesDL.so", "twoDDL/TwoDDL.so", "soundDL/soundDL.so"};

    Game       game(atoi(av[1]),atoi(av[2]), libnames);
    Action::Enum action = Action::NONE;
    
    while(action != Action::ESCAPE) {
        action = game.eventManager();
        game.compute(action);
        game.display();
    }
    
    

    return 0;
}