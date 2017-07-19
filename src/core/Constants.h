//
// Created by montgomery anderson on 30/06/17.
//

#ifndef RECLAIMER_CONSTANTS_H
#define RECLAIMER_CONSTANTS_H


#include <string>

namespace constants {
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 480;

    const std::string VERSION = "0.1";
    const std::string WINDOW_TITLE = "Reclaimer " + VERSION;


    const int WORLD_WIDTH = 1;
    const int WORLD_DEPTH = 1;
    const int CHUNK_SIZE = 64;
    const int TILE_SIZE = 1;
}

#endif //RECLAIMER_CONSTANTS_H
