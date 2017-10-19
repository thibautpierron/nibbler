/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 11:25:21 by tpierron          #+#    #+#             */
/*   Updated: 2017/10/19 10:47:58 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nibbler.hpp"

int     main() {
    srand(time(NULL));

    void *dlHandle = dlopen("mlxDisplay.so", RTLD_LAZY | RTLD_LOCAL);
    if (!dlHandle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(EXIT_FAILURE);
    }

    IgraphLib *(*initContext)(int, int);
    initContext = (IgraphLib *(*)(int, int))dlsym(dlHandle, "initContext");

    IgraphLib *lib = initContext(10, 10);

    // MlxDisplay mlx = MlxDisplay(10, 10);

    std::vector<Vec2> v;
    lib->display(v, v);
    
    // mlx_loop(mlx);
    
    return 0;
}