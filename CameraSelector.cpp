#include "CameraSelector.hpp"
#include <iostream>
// #include <chrono>
// #include <thread>
#include <windows.h>

StateMachine::StateMachine(bool frontState, bool rightstate, bool rearstate, bool leftstate)
{
    frontCameraAvailable = frontState;
    rightCameraAvailable = rightstate;
    rearCameraAvailable = rearstate;
    leftCameraAvailable = leftstate;
    currentState = FRONT;//intially current state is set to FRONT
}

StateMachine::StateMachine() : currentState(FRONT) {}

StateMachine::StateMachine(CameraState initialState) : currentState(initialState) {}

/* function to getState*/
CameraState StateMachine::getState() const
{
return currentState;
}

/* function to setState*/
void StateMachine::setState(CameraState newState, bool isParticipating)
{
currentState = newState;

switch (newState)
{
case FRONT:
    frontCameraAvailable = isParticipating;
    break;
case RIGHT:
    rightCameraAvailable = isParticipating;
    break;
case REAR:
    rearCameraAvailable = isParticipating;
    break;
case LEFT:
    leftCameraAvailable = isParticipating;
    break;
default:
    std::cout << "Invalid camera state specified." << std::endl;
    return;
}
}
    //to check camera participation
bool StateMachine::getIsParticipating(CameraState camera) const
{
switch (camera)
{
case FRONT:
    return frontCameraAvailable;
case RIGHT:
    return rightCameraAvailable;
case REAR:
    return rearCameraAvailable;
case LEFT:
    return leftCameraAvailable;
default:
    std::cout << "Invalid camera state specified." << std::endl;
    return false;
}
}

/*function to get Camera State in "string"*/
std::string StateMachine::cameraStateToString(CameraState state) const
{
switch (state)
{
case FRONT:
    return "FRONT";
case RIGHT:
    return "RIGHT";
case REAR:
    return "REAR";
case LEFT:
    return "LEFT";
default:
    return "INVALID";
}
}

/* function to getNextAvailableCamera */

CameraState StateMachine::getNextAvailableCamera() const
{
CameraState nextCamera = currentState;

do
{
    // Select the next camera in the sequence
    switch (nextCamera)
    {
    case FRONT:
        nextCamera = REAR;
        break;
    case REAR:
        nextCamera = LEFT;
        break;
    case LEFT:
        nextCamera = RIGHT;
        break;
    case RIGHT:
        nextCamera = FRONT;
        break;
    }
} while (!getIsParticipating(nextCamera) || !isAnyCameraAvailable());

    return nextCamera;
}


bool StateMachine::isAnyCameraAvailable() const
{
    return frontCameraAvailable || rightCameraAvailable || rearCameraAvailable || leftCameraAvailable;
}


void StateMachine::updateCameraAvailability(CameraState camera, bool isAvailable)
{
switch (camera)
{
case FRONT:
    frontCameraAvailable = isAvailable;
    break;
case RIGHT:
    rightCameraAvailable = isAvailable;
    break;
case REAR:
    rearCameraAvailable = isAvailable;
    break;
case LEFT:
    leftCameraAvailable = isAvailable;
    break;
    default:
    std::cout << "Invalid camera state specified." << std::endl;
return;
}

std::cout << "Camera " << cameraStateToString(camera) << " availability updated to " << isAvailable << std::endl;

if (!isAvailable && camera == currentState)
{
    // Current camera is not available,, select the next available camera
            CameraState nextCamera = getNextAvailableCamera();
            setState(nextCamera, true);
            std::cout << "Switching to camera " << cameraStateToString(nextCamera) << std::endl;
        }
    }

void StateMachine:: run()
    {
        // std::cout << currentState;
        if (!getIsParticipating(currentState))
            currentState = getNextAvailableCamera();

        // Select the next camera position
        switch (currentState)
        {
        case FRONT:
            std::cout << "Cycle " << cycleCounter + 1 << " -> Front [" << (cycleCounter % CYCLE_COUNT) + 1 << "]" << std::endl;
            break;
        case RIGHT:
            std::cout << "Cycle " << cycleCounter + 1 << " -> Right [" << (cycleCounter % CYCLE_COUNT) + 1 << "]" << std::endl;
            break;
        case REAR:
            std::cout << "Cycle " << cycleCounter + 1 << " -> Rear [" << (cycleCounter % CYCLE_COUNT) + 1 << "]" << std::endl;
            break;
        case LEFT:
            std::cout << "Cycle " << cycleCounter + 1 << " -> Left [" << (cycleCounter % CYCLE_COUNT) + 1 << "]" << std::endl;
            break;
        }

        // Update the current camera and cycle counter
        cycleCounter++;
        if (cycleCounter % CYCLE_COUNT == 0)
        {
            if (isAnyCameraAvailable())
                currentState = getNextAvailableCamera();
            // else
            // {
            //     int ch;
            //     std::cout << "No Camera is active!! Activate camera\n1:Front\t2:Right\n3:Rear\t4:Left\nEnter your choice...\n";
            //     std::cin >> ch;
            //     switch (ch)
            //     {
            //     case 1:
            //         updateCameraAvailability(CameraState::FRONT, true);
            //         break;
            //     case 2:
            //         updateCameraAvailability(CameraState::RIGHT, true);
            //         break;
            //     case 3:
            //         updateCameraAvailability(CameraState::REAR, true);
            //         break;
            //     case 4:
            //         updateCameraAvailability(CameraState::LEFT, true);
            //         break;
            //     default:
            //         std::cout << "Wrong Input";
            //     }
            // }
        }


        // Wait for 30 milliseconds before selecting the next camera
        Sleep(30);
    }