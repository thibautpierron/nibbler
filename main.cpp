/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchevall <mchevall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/26 17:43:43 by mchevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

static void    checkDlError(void *dlHandle) {
    if (!dlHandle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

static void     checkParameters(int ac, char **av) {
    if (ac != 3) {
        std::cerr << "error: need 2 parameters, width & height" << std::endl;
        exit(EXIT_FAILURE);
    }

    long int width = strtol(av[1], NULL, 0);
    long int height = strtol(av[2], NULL, 0);
    if (width == 0L || height == 0L) {
        std::cerr << "error: invalid parameters" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    if (width < 10 || height < 10) {
        std::cerr << "error: parameters minimum is 10" << std::endl;
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
    // void *dlHandle = dlopen("OpenglDL.so", RTLD_LAZY | RTLD_LOCAL);
    void *dlHandle = dlopen("nCursesDL/nCursesDL.so", RTLD_LAZY | RTLD_LOCAL);

    IgraphLib *(*initContext)(int, int);
    initContext = (IgraphLib *(*)(int, int))dlsym(dlHandle, "initContext");
    checkDlError(dlHandle);
    void    (*destroyContext)(IgraphLib *);
    destroyContext = (void(*)(IgraphLib *))dlsym(dlHandle, "destroyContext");
    checkDlError(dlHandle);

    Game       game(atoi(av[1]),atoi(av[2]));
    IgraphLib *lib = initContext(atoi(av[1]),atoi(av[2]));

    Action::Enum action = Action::NONE;
    
    while(action != Action::ESCAPE) {
        action = lib->eventManager();
        
        game.compute(action);
        lib->display(game.getFood(), game.getSnake());
    }
    
    destroyContext(lib);

    dlclose(dlHandle);
    

    return 0;
}