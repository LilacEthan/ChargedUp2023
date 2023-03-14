#pragma once

#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include "Constants.h"
#include <ctre/phoenix/motorcontrol/can/TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/motorcontrol/GroupMotorControllers.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <ctre/phoenix/motorcontrol/ControlMode.h>
#include "rev/CANSparkMax.h"
#include <frc/DoubleSolenoid.h>


class Intake : public frc2::SubsystemBase{
    public:
     Intake();
     
     [[nodiscard]] frc2::CommandPtr IntakeCommand();

     [[nodiscard]] frc2::CommandPtr OuttakeCommand();

     [[nodiscard]] frc2::CommandPtr RetractCommand();
    private:

    ctre::phoenix::motorcontrol::can::WPI_TalonFX IntakeMotor;
    frc::DoubleSolenoid mainIntake{frc::PneumaticsModuleType::REVPH, 
    IntakeConstants::IntakeMainPorts[0], IntakeConstants::IntakeMainPorts[1]};
    frc::DoubleSolenoid intakeJoint{frc::PneumaticsModuleType::REVPH, IntakeConstants::IntakeJointPorts[0], IntakeConstants::IntakeJointPorts[1]};
};