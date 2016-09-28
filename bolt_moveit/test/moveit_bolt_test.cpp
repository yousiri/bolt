/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, PickNik LLC
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of PickNik LLC nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Dave Coleman
   Desc:   Testing for package
*/

/** EXAMPLES:
    EXPECT_FALSE(robot_state.hasFixedLinks());
    EXPECT_EQ(robot_state.getFixedLinksCount(), 0);
    EXPECT_TRUE(robot_state.getPrimaryFixedLink() == NULL);
    EXPECT_GT(robot_state.getFixedLinksMode(), 0);
    EXPECT_LT( fabs(vars[0] - 0), EPSILON) << "Virtual joint in wrong position " << vars[0];
*/

// C++
#include <string>

// ROS
#include <ros/ros.h>

// Testing
#include <gtest/gtest.h>

// OMPL
#include <bolt_core/Bolt.h>
#include <ompl/base/StateSpace.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>

/* Class to hold general test data ------------------------------------------------------ */
class TestingBase
{
public:
  // A shared node handle
  // ros::NodeHandle nh_;

  bool initialize()
  {
    // Allow time to publish messages
    ROS_INFO_STREAM_NAMED("test", "Starting test...");
    return true;
  }
};  // class

/* Create instance of test class ---------------------------------------------------------- */
TestingBase base;

/* Run tests ------------------------------------------------------------------------------ */

// Initialize
TEST(TestingBase, initialize)
{
  ASSERT_TRUE(base.initialize());
}

TEST(TestingBase, get_2d_state_by_vector)
{
  namespace ob = ompl::base;
  namespace ot = ompl::tools;
  namespace otb = ompl::tools::bolt;

  // Setup 2D space
  std::size_t dimensions_ = 2;
  ob::StateSpacePtr space_ = ob::StateSpacePtr(new ob::RealVectorStateSpace(dimensions_));
  EXPECT_TRUE(space_ != NULL);

  // Setup bounds
  ob::RealVectorBounds bounds(dimensions_);
  bounds.setLow(0);
  bounds.setHigh(100);
  space_->as<ob::RealVectorStateSpace>()->setBounds(bounds);
  space_->setup();

  otb::BoltPtr bolt_ = otb::BoltPtr(new otb::Bolt(space_));
  EXPECT_TRUE(bolt_ != NULL);
  bolt_->setup();
  ob::SpaceInformationPtr si_ = bolt_->getSpaceInformation();
  EXPECT_TRUE(si_ != NULL);
  EXPECT_TRUE(si_->isSetup());

  // Example data
  std::vector<double> values(space_->getDimension(), /*default value*/0);
  values[0] = 98;
  values[1] = 99;
  EXPECT_TRUE(values.size() == 2);

  // Create state
  ob::State *candidateState = space_->allocState();
  EXPECT_TRUE(candidateState != NULL);

  // Populate state
  space_->copyFromReals(candidateState, values);
  EXPECT_TRUE(candidateState != NULL);

  // Convert to real vector
  ob::RealVectorStateSpace::StateType *real_state =
    static_cast<ob::RealVectorStateSpace::StateType *>(candidateState);
  EXPECT_TRUE(real_state != NULL);
  EXPECT_TRUE(real_state->values[0]);
  EXPECT_TRUE(real_state->values[1]);
  EXPECT_TRUE(real_state->values[0] == 98);
  EXPECT_TRUE(real_state->values[1] == 99);

  // Get value without real vector
  EXPECT_TRUE((*space_->getValueAddressAtIndex(candidateState, 0)) == 98);
  EXPECT_TRUE((*space_->getValueAddressAtIndex(candidateState, 1)) == 99);

  // Get values into a vector again
  std::vector<double> output_values;
  space_->copyToReals(output_values, candidateState);
  EXPECT_TRUE(output_values.size() == 2);
  EXPECT_TRUE(output_values[0] == 98);
  EXPECT_TRUE(output_values[1] == 99);
}

/* Main  ------------------------------------------------------------------------------------- */
int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "ros_test");
  return RUN_ALL_TESTS();
}
