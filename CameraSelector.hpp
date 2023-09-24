#pragma once

#include <string>

enum CameraState
{
FRONT,
RIGHT,
REAR,
LEFT
};

class StateMachine
{
private:
    CameraState currentState;
    int cycleCounter = 0;
    bool frontCameraParticipating = true;
    bool rightCameraParticipating = true;
    bool rearCameraParticipating = true;
    bool leftCameraParticipating = true;

    bool frontCameraAvailable = true;
    bool rightCameraAvailable = true;
    bool rearCameraAvailable = true;
    bool leftCameraAvailable = true;

    const int CYCLE_COUNT = 3;//cycle count of 3 for ecah camera state
    const int CAMERA_COUNT = 4;//total cameras
    const int TOTAL_CYCLE_COUNT = CYCLE_COUNT * CAMERA_COUNT;
public:
    StateMachine(bool frontState, bool rightstate, bool rearstate, bool leftstate);
    StateMachine();
    StateMachine(CameraState initialState);

    CameraState getState() const;
    void setState(CameraState newState, bool isParticipating);
    bool getIsParticipating(CameraState camera) const;
    std::string cameraStateToString(CameraState state) const;
    CameraState getNextAvailableCamera() const;//to obtain next aavailable camera
    bool isAnyCameraAvailable() const;//to check is any camera is true or false
    void updateCameraAvailability(CameraState camera, bool isAvailable);//to updateCameraAvailabity
    void run();//to run statemachine
};