/**
 * MyProtocol.cpp
 *
 *   Version: 1
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
            //if there was, only have 25% chance of retransmitting
            if (this->rnd() % 100 < 25) {
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    while (localQueueLength != 0) {//transmit your whole queue
                        std::cout << "SLOT - Sending data and hope for no collision." << std::endl;
                        return TransmissionInfo{ Data, localQueueLength };
                    }
                }

            }
            else {
                //do not do anything
                std::cout << "SLOT - Not sending data to give room for others." << std::endl;
                return TransmissionInfo{ Silent, 0 };
            }


        }
        else if (previousMediumState == Idle) {
            if (this->rnd() % 100 < 25) {
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    while (localQueueLength != 0) {//transmit your whole queue
                        std::cout << "SLOT - Sending data and hope for no collision." << std::endl;
                        return TransmissionInfo{ Data, localQueueLength };
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
            if (controlInformation == localQueueLength + 1) {

                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ NoData, 000 };

                }
                else {
                    while (localQueueLength != 0) {//transmit your whole queue
                        std::cout << "SLOT - Sending data and hope for no collision." << std::endl;
                        return TransmissionInfo{ Data, localQueueLength };
                    }
                }



            }
            else if (controlInformation == 000) {
                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ Silent, 0 };

                }
                else {
                    while (localQueueLength != 0) {//transmit your whole queue
                        std::cout << "SLOT - Sending data and hope for no collision." << std::endl;
                        return TransmissionInfo{ Data, localQueueLength };
                    }
                }
            }
            else if (controlInformation == localQueueLength ) {

                // No data to send
                if (localQueueLength == 0) {
                    std::cout << "SLOT - No data to send." << std::endl;
                    return TransmissionInfo{ NoData, 000 };

                }
                else {
                    while (localQueueLength != 0) {//transmit your whole queue
                        std::cout << "SLOT - Sending data and hope for no collision." << std::endl;
                        return TransmissionInfo{ Data, localQueueLength };
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
