/// \file
/// main.cpp

/*
 *  Created on: Jan 29, 2015
 *  Edited:March 2021
 *      Authors: IvanOoijevaar & Marlin Sliman
 *       Group:17
 */

#include "GameObjectStruct.h"
#include "UI.h"
#include "objects.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include<random>


int lives = 3;
int score = 0;
//constructors classes & subclasses
Movers::Movers(int corx, int cory)
{
    x = corx;
    y = cory;
}
Pacman::Pacman(int corx, int cory) : Movers(corx, cory) {
   
}

Ghosts::Ghosts(int corx, int cory) : Movers(corx, cory) {

}

Clyde::Clyde(int cx, int cy) : Ghosts(cx, cy) {}
    /// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
    // Do game loop update here
    return interval;
}

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<std::vector<int>> map = {{
        #include "board.def"

    }};
    std::srand(time(0)); // Initialize random number generator.
    // Create a new ui object
    UI ui(map); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

    // Example object, this can be removed later
    GameObjectStruct pacman;
    pacman.x = 1;
    pacman.y = 1;
    pacman.type = PACMAN;
    pacman.dir = UP;

    GameObjectStruct inky;
    inky.x = 12;
    inky.y = 13;
    inky.type = INKY;
    inky.dir = UP;

     GameObjectStruct pinky;
    pinky.x = 13;
     pinky.y = 13;
    pinky.type = PINKY;
     pinky.dir = UP;

     GameObjectStruct blinky;
     blinky.x = 14;
     blinky.y = 13;
     blinky.type = BLINKY;
     blinky.dir = UP;

     GameObjectStruct clyde;
     clyde.x = 15;
     clyde.y = 13;
     clyde.type = CLYDE;
     clyde.dir = UP;
    
    Pacman paceman (1, 1);//create pacman instance, implement communication with gameobjectstruct later
    Ghosts inkie(12, 13);
    Ghosts pinkie(13, 13);
    Ghosts blinkie(14, 13);
    Clyde clinkie(15, 13);

    // Call game init code here

    clock_t ticking = clock();
    double timelaps;
    double delay = 200;
    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        //collision checks
        if (paceman.getCoordinates("x") == inkie.getCoordinates("x") and paceman.getCoordinates("y") == inkie.getCoordinates("y")) {
            paceman.setCoordinates(1, 1);
            pacman.x = 1;
            pacman.y = 1;
            inkie.setCoordinates(13, 13);
            inky.x = 12;
            inky.y = 13;
            lives = lives - 1;
            continue;
        }
        if (paceman.getCoordinates("x") == pinkie.getCoordinates("x") and
            paceman.getCoordinates("y") == pinkie.getCoordinates("y")) {
            paceman.setCoordinates(1, 1);
            pacman.x = 1;
            pacman.y = 1;
            pinkie.setCoordinates(13, 13);
            pinky.x = 12;
            pinky.y = 13;
            lives = lives - 1;
            continue;
        }
        if (paceman.getCoordinates("x") == blinkie.getCoordinates("x") and
            paceman.getCoordinates("y") == blinkie.getCoordinates("y")) {
            paceman.setCoordinates(1, 1);
            pacman.x = 1;
            pacman.y = 1;
            blinkie.setCoordinates(13, 13);
            blinky.x = 12;
            blinky.y = 13;
            lives = lives - 1;
            continue;
        }
        if (paceman.getCoordinates("x") == clinkie.getCoordinates("x") and
            paceman.getCoordinates("y") == clinkie.getCoordinates("y")) {
            paceman.setCoordinates(1, 1);
            pacman.x = 1;
            pacman.y = 1;
            clinkie.setCoordinates(13, 13);
            clyde.x = 12;
            clyde.y = 13;
            lives = lives - 1;
            continue;
        }
        //check if you are supposed to be dead
        if (lives < 0) {
            std::cout << "GAME OVER\n";
            std::cout << score << std::endl;
            quit = true;        
        }
        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Quit button.
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            std::string direc;
            // All keydown events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT: // YOUR CODE HERE
                    pacman.dir = LEFT;
                    direc = "left";
                    if (paceman.CanIMove( map, direc)) {//see if there is a wall in the direction you want to go
                        
                        paceman.move(direc);//move
                        pacman.x = paceman.getCoordinates("x");//update object (change later?)
                       
                    }
                  
                    break;
                case SDLK_RIGHT: // YOUR CODE HERE
                    pacman.dir = RIGHT;
                    direc = "right";
                     if (paceman.CanIMove( map, direc)) {
                        
                         paceman.move(direc);
                         pacman.x = paceman.getCoordinates("x");
                         
                    }

                    
                    break;
                case SDLK_UP: // YOUR CODE HERE
                    pacman.dir = UP;
                    direc = "up";
                    if (paceman.CanIMove( map, direc)) {
                        
                        paceman.move(direc);
                        pacman.y = paceman.getCoordinates("y");
                       
                    }
                   
                    break;
                case SDLK_DOWN: // YOUR CODE HERE
                    pacman.dir = DOWN;
                    direc = "down";
                    if (paceman.CanIMove( map, direc)) {
                       
                        paceman.move(direc);
                        pacman.y = paceman.getCoordinates("y");
                       
                    }
                   
                   break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
           
            
        }

        // Set the score
        ui.setScore(score); // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(lives); // <-- Pass correct value to the setter

        //move all ghosts
        timelaps = (clock() - ticking);
        std::cout << timelaps << std::endl;
        if (timelaps > delay) {
            inkie.move(inkie.whichWay(map));
            inky.x = inkie.getCoordinates("x");
            inky.y = inkie.getCoordinates("y");

            pinkie.move(pinkie.whichWay(map));
            pinky.x = pinkie.getCoordinates("x");
            pinky.y = pinkie.getCoordinates("y");

            blinkie.move(blinkie.whichWay(map));
            blinky.x = blinkie.getCoordinates("x");
            blinky.y = blinkie.getCoordinates("y");

            clinkie.move(clinkie.whichWay2(map, paceman));
            clyde.x = clinkie.getCoordinates("x");
            clyde.y = clinkie.getCoordinates("y");

            ticking = clock();
        }
        

       // SDL_Delay(100);//bit of delay to prevent ghosts from obtaining speeding tickets. also gives slight input delay to pacman, not optimal

        score = score + 1;//temporary new game: survive the ghosts

        // Render the scene
        std::vector<GameObjectStruct> objects = {pacman, inky, pinky, blinky, clyde};
        // ^-- Your code should provide this vector somehow (e.g.
        // game->getStructs())
        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}

bool Movers::CanIMove( std::vector<std::vector<int>> map, std::string dir)
{ //check for walls, if there are walls in the way do not let the pacman continue
    //x and y are inverted to take care of the inverted coordinates in the map (conversion to standard (x,y))
    if (dir == "left") {
        if (y - 1 < 0) {
            y = 28;
            std::cout << "*WHOOSH* (portal noises)\n";
            return true;
        } else {

            if (map[x][y - 1] == 1) {
                //std::cout << "wall!\n";
                return false;
            } else {
                return true;
            }
        }
    } else if (dir == "right") {
        if (y + 1 > 27) {
            y = -1;
            std::cout << "*WHOOSH* (portal noises)\n";
            return true;
        } else {
            if (map[x][y + 1] == 1) {
               // std::cout << "wall!\n";
                return false;
            } else {
                return true;
            }
        }
    } else if (dir == "up") {
        if (map[x-1][y] == 1) {
            //std::cout << "wall!\n";
            return false;
        } else {
            return true;
        }
    } else if (dir == "down") {
        if (map[x+1][y] == 1) {
            //std::cout << "wall!\n";
            return false;
        } else {
            return true;
        }
    }
}

void Movers::move(std::string dir) {//update the coordinates
    if (dir == "left") {
        y = y - 1;
    } else if (dir == "right") {
        y = y + 1;
    } else if (dir == "up") {
        x = x - 1;
    } else if (dir == "down") {
        x = x + 1;
    }
       
    
}

int Movers::getCoordinates(std::string xy){//obtain coordinates from parent function, inverted here because of the vector layout in map
    if (xy == "y") {
        return x;
    } else {
        return y;
    }
}
void Movers::setCoordinates(int ex, int wy) { 
    x = ex;
    y = wy;
   
}

void Ghosts::setDir(std::string dir) { dirprev = dir; }
std::string Ghosts::getDir() { return dirprev; }

std::string Ghosts::whichWay(std::vector<std::vector<int>> map)
{//determine which way a ghost should go
       
    std::vector<std::string> options;
    if (getCoordinates("x") - 1 < 0) {//ghosts do not go through portals due to interference with their spectral energies
        //therefore if a ghost approaches a portal it turns around
        dirprev = "right";
        return "right";
       // setCoordinates(getCoordinates("x"),28);
        //std::cout << "*WHOOSH* (portal noises)\n";
        
    } else if (getCoordinates("x") + 1 > 27) {
        
        dirprev = "left";
        return "left";
       // setCoordinates(getCoordinates("x"), -1);
       // std::cout << "*WHOOSH* (portal noises)\n";
    } else {
        //check all 4 directions
        if (CanIMove(map, "left")) {
            options.push_back("left");
        }
        if (CanIMove(map, "right")) {
            options.push_back("right");
        }
        if (CanIMove(map, "up")) {
            options.push_back("up");
        }
        if (CanIMove(map, "down")) {
            options.push_back("down");
        }

        if (options.size() == 1) {//if there is only 1 way to go, go that way
            dirprev = options.front();
            return options.front();

        } else if (options.size() > 1) {
            if (options.size() == 2) {//if there are 2, and you can continue forward, do so
                for (int i = 0; i < 2; i++) {
                    if (options[i] == dirprev) {
                        return dirprev;
                    
                       
                    }

                }
                dirprev = options[(rand() % (options.size()))];//else pick randomly one of 2 ways to go
                return dirprev;

            } else {
                dirprev = options[(rand() % (options.size()))];//with bigger crossings, pick 1
                return dirprev;
            }
            
        } else {//debugging else, should not happen
            std::cout << "ERROR!\n";
        }
    }
}

std::string Clyde::whichWay2(std::vector<std::vector<int>> map, Pacman pacman)
{ // determine which way a ghost should go

    std::vector<std::string> options;
    if (getCoordinates("x") - 1 <
        0) { // ghosts do not go through portals due to interference with their
             // spectral energies
        // therefore if a ghost approaches a portal it turns around
        setDir("right");
        return "right";
        // setCoordinates(getCoordinates("x"),28);
        // std::cout << "*WHOOSH* (portal noises)\n";

    } else if (getCoordinates("x") + 1 > 27) {

        setDir("left");
        return "left";
        // setCoordinates(getCoordinates("x"), -1);
        // std::cout << "*WHOOSH* (portal noises)\n";
    } else {
        // check all 4 directions
        if (CanIMove(map, "left")) {
            options.push_back("left");
        }
        if (CanIMove(map, "right")) {
            options.push_back("right");
        }
        if (CanIMove(map, "up")) {
            options.push_back("up");
        }
        if (CanIMove(map, "down")) {
            options.push_back("down");
        }

        if (options.size() == 1) { // if there is only 1 way to go, go that way
            setDir(options.front());
            return options.front();

        } else if (options.size() > 1) {
            if (options.size() == 2) { // if there are 2, and you can continue forward, do so
                for (int i = 0; i < 2; i++) {
                    if (options[i] == getDir()) {
                        return getDir();
                    }
                }

                int x = pacman.getCoordinates("x");
                int y = pacman.getCoordinates("y");
                for (int i = 0; i < options.size(); i++) {//locate the best option to get closer to pacman
                    if (options[i] == "left") {
                        if (abs(x - (getCoordinates("x") - 1)) < abs(x - getCoordinates("x"))) {
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "right") {
                        if (abs(x - (getCoordinates("x") + 1)) < abs(x - getCoordinates("x"))) {
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "up") {
                        if (abs(y - (getCoordinates("y") - 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "down") {
                        if (abs(y - (getCoordinates("y") + 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    }
                }
                setDir(options[(rand() % (options.size()))]);//if no option is better, pick random
                return getDir();

            } else {//same here for crossroads
                int x = pacman.getCoordinates("x");
                int y = pacman.getCoordinates("y");
                for (int i = 0; i < options.size(); i++) {
                    if (options[i] == "left") {
                        if (abs(x - (getCoordinates("x") - 1)) < abs(x - getCoordinates("x"))) {
                           
                            
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "right") {
                        if (abs(x - (getCoordinates("x") + 1)) <  abs(x - getCoordinates("x"))) {
                           
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "up") {
                        if (abs(y - (getCoordinates("y") - 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDir(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "down") {
                        if (abs(y - (getCoordinates("y") + 1)) < abs(y - getCoordinates("y"))) {
                            setDir(options[i]);
                            return options[i];
                        }
                    }
                }

                setDir(options[(rand() % (options.size()))]);
                return getDir();
            }

        } else { // debugging else, should not happen
            std::cout << "ERROR!\n";
        }
    }
}



