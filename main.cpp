#include "CameraSelector.hpp"
#include <iostream>
// #include <chrono>
// #include <thread>


int main()
{

    // const int numCycles = 3;

    // for (int i = 0; i < numCycles * 4; i++) {
    //     CameraState nextCamera = cameraStateMachine.getNextAvailableCamera();
    //     cameraStateMachine.setState(nextCamera, true);
    //     cameraStateMachine.updateCameraAvailability(nextCamera, false);

    //     std::cout << "Current state: " << cameraStateMachine.cameraStateToString(cameraStateMachine.getState()) << std::endl;
    //     std::cout << "Is participating: " << cameraStateMachine.getIsParticipating(nextCamera) << std::endl;

    //     std::this_thread::sleep_for(std::chrono::milliseconds(30));
    // }


    // take bool input either 0-inactive, 1-active 
    bool frontState, rightState, rearState, leftState, startState;
    std::cout << "Enter State of Front Camera(0-inactive, 1-active):\n";
    std::cin >> frontState;
    std::cout << "Enter State of Right Camera(0-inactive, 1-active):\n";
    std::cin >> rightState;
    std::cout << "Enter State of Rear Camera(0-inactive, 1-active):\n";
    std::cin >> rearState;
    std::cout << "Enter State of Left Camera(0-inactive, 1-active):\n";
    std::cin >> leftState;


    StateMachine cameraStateMachine(frontState, rightState, rearState, leftState);

    while (true)
    {
        cameraStateMachine.run();
    }
    return 0;
}

// To run this type below command
// g++ -o main.exe main.cpp CameraSelector.cpp
