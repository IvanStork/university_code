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
int eat = 0;
//constructors classes & subclasses
Game::Game(int cx, int cy)
{
    x = cx;
    y = cy;
}

Pacman::Pacman(int corx, int cory, Type type, Direction dir)
    : Game(corx, cory)
{
    setStruct(corx, cory, type, dir);
}

Ghosts::Ghosts(int corx, int cory, Type type, Direction dir) : Game(corx, cory) {
    setStruct(corx, cory, type, dir);
}

Clyde::Clyde(int cx, int cy, Type type, Direction dir)
    : Ghosts(cx, cy, type, dir)
{
    setStruct(cx, cy, type, dir);
}

Edibles::Edibles(int cx, int cy, Type type, Direction dir) : Game(cx, cy) {
    setStruct(cx, cy, type, dir);
    x = cx;
    y = cy;
}
std::vector<Game> dots;//vector to store all dots
void drawdots(std::vector<std::vector<int>>);

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
    UI ui(map); // <-- use map from your game objects

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

    Pacman pacman (1, 1, PACMAN, UP);//create pacman and ghosts
    
    Ghosts inky(12, 13, INKY, UP);
    
    Ghosts pinky(13, 13, PINKY, UP);
   
    Ghosts blinky(14, 13, BLINKY, UP);
    
    Clyde clyde(15, 13, CLYDE, UP);
    //create energizers and fruit
    Edibles energizer1(2, 1, ENERGIZER, UP);
 
    Edibles energizer2(26, 1, ENERGIZER, UP);
  
    Edibles energizer3(26, 25, ENERGIZER, UP);
  
    Edibles energizer4(1, 25, ENERGIZER, UP);
    Edibles strawberry(21, 21, STRAWBERRY, UP);
   
    Edibles lemon(13, 13, LEMON, UP);
  
    Edibles orange(6, 15, ORANGE, UP);
    
    Edibles cherry(16, 5,CHERRY, UP);
    
    Edibles grapes(21, 19, GRAPES, UP);
 
    Edibles apple(15, 21, APPLE, UP);
    
    
    
    drawdots(map);//add dots to their special vector
    // Call game init code here

    clock_t ticking = clock();//initialize timer for the ghosts to move
    double timelaps;
    double delay = 200;//set delay in milliseconds (feel free to lowe this to increase difficulty)

    clock_t energyzerEaten;//initialize timer for when energizer is eaten
    double timePassed;
    double over = 10000;
    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        std::vector<Game> store; // storage for all objects(not dots/fruit yet)

        // collide with energizer
        if (pacman.getCoordinates("x") == energizer1.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer1.getCoordinates("x") ||
            pacman.getCoordinates("x") == energizer2.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer2.getCoordinates("x") ||
            pacman.getCoordinates("x") == energizer3.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer3.getCoordinates("x") ||
            pacman.getCoordinates("x") == energizer4.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer4.getCoordinates("x")) {

            if (pacman.getCoordinates("x") == energizer1.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer1.getCoordinates("x")) {
                energizer1.setCoordinates(6, 29);
                
            }

            if (pacman.getCoordinates("x") == energizer2.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer2.getCoordinates("x")) {
                energizer2.setCoordinates(6, 29);
                
            }

            if (pacman.getCoordinates("x") == energizer3.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer3.getCoordinates("x")) {
                energizer3.setCoordinates(6, 29);
                
            }

            if (pacman.getCoordinates("x") == energizer4.getCoordinates("y") &&
                pacman.getCoordinates("y") == energizer4.getCoordinates("x")) {
                energizer4.setCoordinates(6, 29);
                
            }
            //ghosts can now be eaten
            inky.setType(SCARED);
            inky.setEat(true);
            pinky.setType(SCARED);
            pinky.setEat(true);
            blinky.setType(SCARED);
            blinky.setEat(true);
            clyde.setType(SCARED);
            clyde.setEat(true);
            eat = 1;
            energyzerEaten = clock();//start timer

        }
        //collision checks
        if (pacman.getCoordinates("x") == inky.getCoordinates("x") and
            pacman.getCoordinates("y") == inky.getCoordinates("y")) {

            if (inky.getEat()) {//see if the ghosts can be eaten right now, if not, pacman dies
                inky.setCoordinates(13, 13);//return ghost to start position
                inky.setEat(false);
                inky.setType(INKY);
                score = score + 100;
                continue;
            } else {
                //return pacman and ghost to start position
                pacman.setCoordinates(1, 1);

                inky.setCoordinates(13, 13);
                // remove 1 life
                lives = lives - 1;
                continue;
            }
        }
        if (pacman.getCoordinates("x") == pinky.getCoordinates("x") and pacman.getCoordinates("y") == pinky.getCoordinates("y")) {
            
            
            if (pinky.getEat()) {
                pinky.setCoordinates(13, 13);
                pinky.setEat(false);
                pinky.setType(PINKY);
                score = score + 100;
                continue;
            } else {

                pacman.setCoordinates(1, 1);

                pinky.setCoordinates(13, 13);
                // remove 1 life
                lives = lives - 1;
                continue;
            }
        }
        if (pacman.getCoordinates("x") == blinky.getCoordinates("x") and pacman.getCoordinates("y") == blinky.getCoordinates("y")) {
            
            
            if (blinky.getEat()) {
                blinky.setCoordinates(13, 13);
                blinky.setEat(false);
                blinky.setType(BLINKY);
                score = score + 100;
                continue;
            } else {

                pacman.setCoordinates(1, 1);

                blinky.setCoordinates(13, 13);
                // remove 1 life
                lives = lives - 1;
                continue;
            }
        }
        if (pacman.getCoordinates("x") == clyde.getCoordinates("x") and pacman.getCoordinates("y") == clyde.getCoordinates("y")) {
            
            
            if (clyde.getEat()) {
                clyde.setCoordinates(13, 13);
                clyde.setEat(false);
                clyde.setType(CLYDE);
                score = score + 100;
                continue;
            } else {

                pacman.setCoordinates(1, 1);

                clyde.setCoordinates(13, 13);
                // remove 1 life
                lives = lives - 1;
                continue;
            }
        }
        //check if you are supposed to be dead
        if (lives < 0) {
            std::cout << "GAME OVER\n";
            std::cout << score << std::endl;
            quit = true;        
        }
        //check if you fisished the game
        if (dots.size() <= 0) {
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
                case SDLK_LEFT: 
                    
                    
                    direc = "left";
                    if (pacman.CanIMove( map, direc)) {//see if there is a wall in the direction you want to go
                       pacman.move(direc);//move
                       
                         for (int e = 0; e < dots.size(); e++) {//see if you collided with a dot
                           
                               if ((pacman.getCoordinates("x") == dots[e].getStruct().x) &&
                                 (pacman.getCoordinates("y") == dots[e].getStruct().y)) {
                                   score++;
                                   dots.erase(dots.begin() + (e));
                               }
                           
                         }
                    }
                  
                    break;
                case SDLK_RIGHT: 
                   

                    direc = "right";
                     if (pacman.CanIMove( map, direc)) {
                        pacman.move(direc);
                         
                         for (int e = 0; e < dots.size(); e++) {

                            if ((pacman.getCoordinates("x") ==
                                 dots[e].getStruct().x) &&
                                (pacman.getCoordinates("y") ==
                                 dots[e].getStruct().y)) {
                                score++;
                                dots.erase(dots.begin() + (e));
                            }
                        }
                    }

                    
                    break;
                case SDLK_UP: 
                   
                    direc = "up";
                    if (pacman.CanIMove( map, direc)) {
                       pacman.move(direc);
                       
                        for (int e = 0; e < dots.size(); e++) {

                           if ((pacman.getCoordinates("x") ==
                                dots[e].getStruct().x) &&
                               (pacman.getCoordinates("y") ==
                                dots[e].getStruct().y)) {
                               score++;
                               dots.erase(dots.begin() + (e));
                           }
                       }
                    }
                   
                    break;
                case SDLK_DOWN: 
                    
                    direc = "down";
                    if (pacman.CanIMove( map, direc)) {
                       pacman.move(direc);
                       
                        for (int e = 0; e < dots.size(); e++) {

                           if ((pacman.getCoordinates("x") ==
                                dots[e].getStruct().x) &&
                               (pacman.getCoordinates("y") ==
                                dots[e].getStruct().y)) {
                               score++;
                               dots.erase(dots.begin() + (e));
                           }
                       }
                    }
                   
                   break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
           
            
        }
        if (pacman.getCoordinates("x") == strawberry.getCoordinates("y") and
            pacman.getCoordinates("y") == strawberry.getCoordinates("x")) {
            score = score + 200;
            strawberry.setCoordinates(29, 29);
        }
        if (pacman.getCoordinates("x") == lemon.getCoordinates("y") and
            pacman.getCoordinates("y") == lemon.getCoordinates("x")) {
            score = score + 200;
            lemon.setCoordinates(29, 29);
        }
        if (pacman.getCoordinates("x") == orange.getCoordinates("y") and
            pacman.getCoordinates("y") == orange.getCoordinates("x")) {
            score = score + 200;
            orange.setCoordinates(29, 29);
        }
        if (pacman.getCoordinates("x") == cherry.getCoordinates("y") and
            pacman.getCoordinates("y") == cherry.getCoordinates("x")) {
            score = score + 200;
            cherry.setCoordinates(29, 29);
        }
        if (pacman.getCoordinates("x") == grapes.getCoordinates("y") and
            pacman.getCoordinates("y") == grapes.getCoordinates("x")) {
            score = score + 200;
            grapes.setCoordinates(29, 29);
        }
        if (pacman.getCoordinates("x") == apple.getCoordinates("y") and
            pacman.getCoordinates("y") == apple.getCoordinates("x")) {
            score = score + 200;
            apple.setCoordinates(29, 29);
        }
        // Set the score
        ui.setScore(score); 

        // Set the amount of lives
        ui.setLives(lives); 

        
        timelaps = (clock() - ticking);
        
        if (timelaps > delay) {//slow down the ghosts, otherwise the game is too difficult
            //move ghosts
            inky.move(inky.whichWay(map));
           
            pinky.move(pinky.whichWay(map));
           
            blinky.move(blinky.whichWay(map));
           
            clyde.move(clyde.whichWay2(map, pacman));
           
            ticking = clock();
        }
        //add all objects to a vector to make the render function easier
        store.push_back(pacman);
        store.push_back(inky);
        store.push_back(pinky);
        store.push_back(blinky);
        store.push_back(clyde);
        store.push_back(energizer1);
        store.push_back(energizer2);
        store.push_back(energizer3);
        store.push_back(energizer4);
        store.push_back(strawberry);
        store.push_back(lemon);
        store.push_back(orange);
        store.push_back(cherry);
        store.push_back(apple);
        store.push_back(grapes);

        

        // Render the scene
        std::vector<GameObjectStruct> objects;
        for (int i = 0; i < dots.size(); i++) {//render dots first, otherwise you can only see the dots
            objects.push_back(dots[i].getStruct());
            
        }
        for (int i = 0; i < store.size(); i++) {
            objects.push_back(store[i].getStruct());
        }
        
       
        ui.update(objects);

        if (eat == 1) {//see if the ghosts need to be dangerous again

            timePassed = clock() - energyzerEaten;
            if (timePassed > over) {
                inky.setType(INKY);
                inky.setEat(false);
                pinky.setType(PINKY);
                pinky.setEat(false);
                blinky.setType(BLINKY);
                blinky.setEat(false);
                clyde.setType(CLYDE);
                clyde.setEat(false);
            }
        }

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}

bool Game::CanIMove( std::vector<std::vector<int>> map, std::string dir)
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

void Game::move(std::string dir) {//update the coordinates
    if (dir == "left") {
        y = y - 1;//update class coordinates
        object.x = y;//update struct coordinates
        object.dir = LEFT;//also update the direction of the object
    } else if (dir == "right") {
        y = y + 1;
        object.x = y;
        object.dir = RIGHT;
    } else if (dir == "up") {
        x = x - 1;
        object.y = x;
        object.dir = UP;
    } else if (dir == "down") {
        x = x + 1;
        object.y = x;
        object.dir = DOWN;
    }
       
    
}

int Game::getCoordinates(std::string xy){//obtain coordinates from parent function, inverted here because of the vector layout in map
    if (xy == "y") {
        return x;
    } else {
        return y;
    }
}
void Game::setCoordinates(int ex, int wy) { 
    x = ex;
    y = wy;
    object.x = ex;
    object.y = wy;
}

GameObjectStruct Game::getStruct() { return object; }
void Game::setStruct(int ex, int wy, Type type, Direction way) {
    object.x = ex;
    object.y = wy;
    object.type = type;
    object.dir = way;
}
void Game::setType(Type type) { object.type = type; }

void Ghosts::setDirprev(std::string dir) { dirprev = dir; }
std::string Ghosts::getDirprev() { return dirprev; }

void Ghosts::setEat(bool can) { canBeEaten = can; }
bool Ghosts::getEat() { return canBeEaten; }

std::string Ghosts::whichWay(std::vector<std::vector<int>> map)
{//determine which way a ghost should go
       
    std::vector<std::string> options;
    if (getCoordinates("x") - 1 < 0) {//ghosts do not go through portals due to interference with their spectral energies
        //therefore if a ghost approaches a portal it turns around
        dirprev = "right";
        return "right";
      
        
    } else if (getCoordinates("x") + 1 > 27) {
        
        dirprev = "left";
        return "left";
     
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
        setDirprev("right");
        return "right";
       

    } else if (getCoordinates("x") + 1 > 27) {

        setDirprev("left");
        return "left";
        
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
            setDirprev(options.front());
            return options.front();

        } else if (options.size() > 1) {
            if (options.size() == 2) { // if there are 2, and you can continue forward, do so
                for (int i = 0; i < 2; i++) {
                    if (options[i] == getDirprev()) {
                        return getDirprev();
                    }
                }

                int x = pacman.getCoordinates("x");
                int y = pacman.getCoordinates("y");
                for (int i = 0; i < options.size(); i++) {//locate the best option to get closer to pacman
                    if (options[i] == "left") {
                        if (abs(x - (getCoordinates("x") - 1)) < abs(x - getCoordinates("x"))) {
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "right") {
                        if (abs(x - (getCoordinates("x") + 1)) < abs(x - getCoordinates("x"))) {
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "up") {
                        if (abs(y - (getCoordinates("y") - 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "down") {
                        if (abs(y - (getCoordinates("y") + 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    }
                }
                setDirprev(options[(rand() % (options.size()))]);//if no option is better, pick random
                return getDirprev();

            } else {//same here for crossroads
                int x = pacman.getCoordinates("x");
                int y = pacman.getCoordinates("y");
                for (int i = 0; i < options.size(); i++) {
                    if (options[i] == "left") {
                        if (abs(x - (getCoordinates("x") - 1)) < abs(x - getCoordinates("x"))) {
                           
                            
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "right") {
                        if (abs(x - (getCoordinates("x") + 1)) <  abs(x - getCoordinates("x"))) {
                           
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "up") {
                        if (abs(y - (getCoordinates("y") - 1)) < abs(y - getCoordinates("y"))) {
                           
                            setDirprev(options[i]);
                            return options[i];
                        }
                    } else if (options[i] == "down") {
                        if (abs(y - (getCoordinates("y") + 1)) < abs(y - getCoordinates("y"))) {
                            setDirprev(options[i]);
                            return options[i];
                        }
                    }
                }

                setDirprev(options[(rand() % (options.size()))]);
                return getDirprev();
            }

        } else { // debugging else, should not happen
            std::cout << "ERROR!\n";
        }
    }
}

void drawdots(std::vector<std::vector<int>> map)
{//make a dot object for every 0 on the map, and add the objects to a vector
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                Edibles dot(j, i, DOT, UP);
               
                dots.push_back(dot);
            }
        }
    }
}


