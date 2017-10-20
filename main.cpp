/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/20 13:20:32 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

static void    checkDlError(void *dlHandle) {
    if (!dlHandle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

int     main() {
    srand(time(NULL));

    void *dlHandle = dlopen("OpenglDL.so", RTLD_LAZY | RTLD_LOCAL);

    IgraphLib *(*initContext)(int, int);
    initContext = (IgraphLib *(*)(int, int))dlsym(dlHandle, "initContext");
    checkDlError(dlHandle);
    void    (*destroyContext)(IgraphLib *);
    destroyContext = (void(*)(IgraphLib *))dlsym(dlHandle, "destroyContext");
    checkDlError(dlHandle);

    Game game(10,10);
    IgraphLib *lib = initContext(10, 10);

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