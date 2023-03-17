#include "subsystems/Elevator.h"
//#include <frc/smartdashboard/SmartDashboard.h>
//#include <frc/shuffleboard/Shuffleboard.h>
using namespace ElevatorConstants;

Elevator::Elevator(){
    rgtElevator.ConfigFactoryDefault();
    lftElevator.ConfigFactoryDefault();
    rgtElevator.SetInverted(true);
    lftElevator.Follow(rgtElevator);
}

frc2::CommandPtr Elevator::ElevatorFlipOut(){
    return RunOnce([this] {Extension.Set(frc::DoubleSolenoid::kReverse);})
    // .AlongWith(Run([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, .25);}))
    // .WithTimeout(2.0_s)
    // .AndThen(Run([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);}))
    .WithName("Flip Out");
}

frc2::CommandPtr Elevator::ElevatorRetract(){
    return RunOnce([this] {Extension.Set(frc::DoubleSolenoid::kForward);})
    .WithName("Retract Elevator");
}

frc2::CommandPtr Elevator::ElevatorFwd(){
    return RunOnce([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.25);})
    .WithName("lol");
}

frc2::CommandPtr Elevator::ElevatorBk(){
    return RunOnce([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.25);})
    .WithName("Lamao");
}

frc2::CommandPtr Elevator::ElevatorStop(){
    return RunOnce([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);})
    .WithName("lame");
}

frc2::CommandPtr Elevator::ElevatorBreak(){
    return RunOnce([this] {rgtElevator.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);})
    .AndThen(Run([this] {rgtElevator.Set(ctre::phoenix::motorcontrol::TalonFXControlMode::PercentOutput, 0);}))
    .WithName("u bozo");
}

frc2::CommandPtr Elevator::EleCoast(){
    return RunOnce([this] {rgtElevator.SetNeutralMode(ctre::phoenix::motorcontrol::Coast);})
    .WithName("dog");
}