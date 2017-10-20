/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/20 10:38:15 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

static void    checkDlError(void *dlHandle) {
    if (!dlHandle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }
}

static std::vector<Vec2>    initSnake() {
    std::vector<Vec2> data;
    data.push_back(Vec2(3, 3));
    data.push_back(Vec2(3, 4));
    data.push_back(Vec2(3, 5));
    data.push_back(Vec2(3, 6));
    return data;
}

static std::vector<Vec2>    initFood() {
    std::vector<Vec2> data;
    data.push_back(Vec2(0, 0));
    data.push_back(Vec2(9, 9));
    return data;
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

    IgraphLib *lib = initContext(10, 10);

    std::vector<Vec2> food = initFood();
    std::vector<Vec2> snake = initSnake();
    Action::Enum action = Action::NONE;
    
    while(action != Action::ESCAPE) {
        action = lib->eventManager();
        lib->display(food, snake);
    }
    
    destroyContext(lib);

    dlclose(dlHandle);
    

    return 0;
}