#include "subsystems/Swivel.h"
#include <frc/smartdashboard/SmartDashboard.h>
//#include <frc/shuffleboard/Shuffleboard.h>
#include <ctre/phoenix/motorcontrol/StatorCurrentLimitConfiguration.h>


using namespace SwivelConstants;

Swivel::Swivel(){
    swivelMotor.ConfigFactoryDefault();
    swivelMotor.SetInverted(true);
    swivelMotor.ConfigPeakCurrentLimit(0);
    swivelMotor.SetSensorPhase(true);
    swivelMotor.SelectProfileSlot(0, 0);
    swivelMotor.Config_kF(0, SwivelConstants::SwivelkF, 10);
    swivelMotor.Config_kP(0, SwivelConstants::SwivelkP, 10);
    swivelMotor.Config_kI(0,SwivelConstants::SwivelkI, 10);
    swivelMotor.Config_kD(0, SwivelConstants::SwivelkD, 10);

    swivelMotor.ConfigMotionCruiseVelocity(SwivelConstants::CruiseVel, 10);
    swivelMotor.ConfigMotionAcceleration(SwivelConstants::SwivelAccl, 10);
}

void Swivel::resetSwivel(){
    swivelMotor.SetSelectedSensorPosition(0, 0, 10);
}

void Swivel::setSwivel(int pow){
    swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, pow);
}

int Swivel::getSwivel(){
    return swivelMotor.GetSelectedSensorPosition();
}
frc2::CommandPtr Swivel::SwivelDownCommand(){
    //For picking up from the ground
    return Run([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.6);
                            if(swivelMotor.GetSelectedSensorPosition() < down){
                                swivelMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
                                swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);
                            }})
    .WithName("Swivel Down Position");
}

frc2::CommandPtr Swivel::PrepSwivelCommand(){
    //Prep for pickup up from feeder station
    return Run([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.6);
                        if(swivelMotor.GetSelectedSensorPosition() > SwivelConstants::prep){
                            swivelMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
                            swivelMotor.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, 0.03);    
                        }})
    .WithName("Swivel Prep Position");
}

frc2::CommandPtr Swivel::FeederSwivel(){
    return Run([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.6);
                        if(swivelMotor.GetSelectedSensorPosition() > SwivelConstants::feeder){
                            swivelMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
                            swivelMotor.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, 0.03);
                        }})
                        .WithName("Feeder Position");
}

frc2::CommandPtr Swivel::SwivelScoreCommand(){
    //Put in scoring position
    return Run([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.8);
                        if(swivelMotor.GetSelectedSensorPosition() > SwivelConstants::score){
                            swivelMotor.SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);
                            swivelMotor.Set(ctre::phoenix::motorcontrol::TalonSRXControlMode::PercentOutput, 0);
                            
                        }})
                        
    .WithName("Swivel Score Position");
}

frc2::CommandPtr Swivel::SwivelFwd(){
    return RunOnce([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0.7);})
    .WithName("swivel forward");
}

frc2::CommandPtr Swivel::SwivelBk(){    //Reverse
    return RunOnce([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, -0.5);})
    .WithName("Reverse swivel");
}

frc2::CommandPtr Swivel::SwivelStop(){
    return RunOnce([this] {swivelMotor.Set(ctre::phoenix::motorcontrol::ControlMode::PercentOutput, 0);})
    .WithName("stop swivel");
}

frc2::CommandPtr Swivel::ZeroSwivel(){
    return RunOnce([this] {Swivel::resetSwivel();})
    .WithName("Zero Swivel");
}

void Swivel::Periodic(){
    frc::SmartDashboard::PutNumber("Swivel Voltage", swivelMotor.GetSupplyCurrent());
    frc::SmartDashboard::PutNumber("Swivel Temp", swivelMotor.GetTemperature());
    frc::SmartDashboard::PutNumber("Swivel Enc", swivelMotor.GetSelectedSensorPosition());
}