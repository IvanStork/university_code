/**
 * MyProtocol.cpp
 *
 *   Version: 2
 *    Author: Ivan Ooijevaar & Marlin Sliman.
 * Copyright: University of Twente, 2015-2019
 *
 **************************************************************************
 *                            Copyright notice                            *
 *                                                                        *
 *             This file may ONLY be distributed UNMODIFIED.              *
 * In particular, a correct solution to the challenge must NOT be posted  *
 * in public places, to preserve the learning effect for future students. *
 **************************************************************************
 */

#include "MyProtocol.h"
int count = 0;
namespace my_protocol {
   
    MyProtocol::MyProtocol() {
        unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count(); // This grabs the lower 32 bits for our seed.
        this->rnd = std::default_random_engine(seed);
    }

    MyProtocol::~MyProtocol() {
    }

    TransmissionInfo MyProtocol::TimeslotAvailable(
        MediumState previousMediumState, int32_t controlInformation, int localQueueLength) {
        //check if there was a collision
        if (previousMediumState == Collision) {
            std::cout << "collision ";
            //if there was, only have 25% chance of retransmitting
            if (this->rnd() % 100 < 25) {
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {//there is data in the queue
                    if (count < 6) {//transmit 7 packets max
                        std::cout << "SLOT - Sending data. " << count << std::endl;
                        count = count + 1;
                        return TransmissionInfo{ Data, localQueueLength };


                    }
                    else {//if this client already sent 7, see if anyone else wants to send
                        count = 0;
                        return TransmissionInfo{ NoData, 1000 };

                    }
                }

            }
            else {
                //do not do anything
                std::cout << "SLOT - Not sending data to give room for others." << std::endl;
                return TransmissionInfo{ Silent, 0 };
            }


        }
        else if (previousMediumState == Idle) {//check if the previous slot was idle
            std::cout << "idle ";
            count = 0;      //if it was idle then string was cut off, so for more efficiency start over
            if (this->rnd() % 100 < 60) {
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    //send data to restart strings of data
                    std::cout << "SLOT - Sending data. " << count << std::endl;
                    count = count + 1;
                    return TransmissionInfo{ Data, localQueueLength };


                }
            }
            else {
                //do not do anything
                std::cout << "SLOT - Not sending data to give room for others." << std::endl;
                return TransmissionInfo{ Silent, 0 };
            }

        }
        else if (controlInformation == 1000) {  //a client asked if anyone wants to sent data, react
            std::cout << "New try ";
            if (this->rnd() % 100 < 60) {//60% chance to react, to minimize no reactions but also collisions
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    if (count < 6) {//transmit 7 packets max
                        std::cout << "SLOT - Sending data." << count << std::endl;
                        count = count + 1;
                        return TransmissionInfo{ Data, localQueueLength };

                    }
                    else {
                        count = 0;
                        return TransmissionInfo{ NoData, 1000 };

                    }
                }

            }
            else {
                //do not do anything
                std::cout << "SLOT - Not sending data to give room for others." << std::endl;
                return TransmissionInfo{ Silent, 0 };
            }
        }
        
        else {
            if (controlInformation == localQueueLength + 1) {   //using length of queue to distinguish between clients to keep a string of 7 packets
                                                                //known issue: 2 queues of the same length increases collisions
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    if (count < 6) {//transmit 7 packets max
                        std::cout << "SLOT - Sending data and hope for no collision." << count << std::endl;
                        count = count + 1;
                        return TransmissionInfo{ Data, localQueueLength };
                       
                    }
                    else {
                        count = 0;
                        return TransmissionInfo{ NoData, 1000 };
                        
                    }
                }



            }
           
            else if (controlInformation == localQueueLength ) {// using length of queue again, but specified at 1 more to lower idles because of additions to the queue

                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    if (count < 6) {//transmit 7 packets max
                        std::cout << "SLOT - Sending data and hope for no collision." << count << std::endl;
                        count = count + 1;
                        return TransmissionInfo{ Data, localQueueLength };
                        
                       
                    }
                    else {
                        count = 0;
                        return TransmissionInfo{ NoData, 1000 };
                        
                    }
                }
            }
            else {
                //do not do anything
                std::cout << "SLOT - Not sending data to give room for others." << std::endl;
                return TransmissionInfo{ Silent, 0 };
            }
        }
    }
} /* namespace my_protocol */
