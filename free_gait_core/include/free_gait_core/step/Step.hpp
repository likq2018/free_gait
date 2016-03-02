/*
 * Step.hpp
 *
 *  Created on: Jan 20, 2015
 *      Author: Péter Fankhauser
 *   Institute: ETH Zurich, Autonomous Systems Lab
 */

#pragma once

// STL
#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>

// Free Gait
#include "free_gait_core/TypeDefs.hpp"
#include "free_gait_core/leg_motion/LegMotionBase.hpp"
#include "free_gait_core/base_motion/BaseMotionBase.hpp"

namespace free_gait {

class LegMotionBase;
class BaseMotionBase;

class Step
{
 public:
  Step();
  virtual ~Step();
  Step(const Step& other);
  Step& operator=(const Step& other);

  /*!
   * Type definitions.
   */
  typedef std::unordered_map<LimbEnum, std::unique_ptr<LegMotionBase>, EnumClassHash> LegMotions;

  /*!
   * Add step data (simplified input).
   * @param stepNumber the step number.
   * @param legName the name of the leg.
   * @param position the desired position of the step in world frame.
   */
//  void addSimpleStep(const int stepNumber, const std::string& legName, const free_gait::Position& position);

  /*!
   * Add swing data for a leg.
   * @param legName the name of the leg.
   * @param data the step data.
   */
  void addLegMotion(const LimbEnum& limb, const LegMotionBase& legMotion);

  /*!
   * Add base shift data for a state.
   * @param state the corresponding state of the base shift data.
   * @param data the base shift data.
   */
  void addBaseMotion(const BaseMotionBase& baseMotion);

  bool update();
  bool isUpdated() const;

  /*!
   * Checks if step has all data.
   * @return true if complete, false otherwise.
   */
  bool isComplete() const;

  /*!
   * Advance in time
   * @param dt the time step to advance [s].
   * @return true if step is active, false if finished.
   */
  bool advance(double dt);

  /*!
   * Returns the swing data as a map between leg name and swing data.
   * @return the swing data map.
   */
  bool hasLegMotion() const;
  bool hasLegMotion(const LimbEnum& limb) const;
  const LegMotionBase& getLegMotion(const LimbEnum& limb) const;

  bool hasBaseMotion() const;
  const BaseMotionBase& getBaseMotion() const;

  /*!
   * Return the current time of the step, starting at 0.0 for each step.
   * @return the current time.
   */
  double getTime() const;
  double getTotalDuration() const;
  double getTotalPhase() const;
  double getLegMotionDuration(const LimbEnum& limb) const;
  double getLegMotionPhase(const LimbEnum& limb) const;
  double getBaseMotionDuration() const;
  double getBaseMotionPhase() const;

  bool requiresMultiThreading() const;
  bool isApproachingEnd(double tolerance) const;

  friend std::ostream& operator << (std::ostream& out, const Step& step);

  friend class StepCompleter;

 protected:
  bool isComplete_;
  LegMotions legMotions_;
  std::unique_ptr<BaseMotionBase> baseMotion_;

 private:
  //! Current time, starts at 0.0 at each step.
  double time_;
  double totalDuration_;
  bool isUpdated_;

};

} /* namespace */
