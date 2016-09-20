/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2016, University of Colorado, Boulder
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
   Desc:   Main executable
*/

// this package
#include <bolt_moveit/bolt_moveit.h>

int main(int argc, char **argv)
{
  // Initialize ROS
  ros::init(argc, argv, "bolt_moveit");
  ROS_INFO_STREAM_NAMED("main", "Starting BoltHilgendorf...");

  // Allow the action server to recieve and send ros messages
  ros::AsyncSpinner spinner(2);
  spinner.start();

  // Get name of this computer
  char hostname[1024];
  gethostname(hostname, 1024);
  std::cout << "hostname: " << hostname << std::endl;

  // std::cout << "before get env " << std::endl;
  // const std::string hostname2 = hostname;
  // const std::string home = getenv("HOME");
  // std::cout << "getEnv: " << home << std::endl;

  // if (hostname2 != "ros-monster" && home.empty())
  //   std::cout << "its true! " << std::endl;

  // {
  //   setenv("HOME", "/home/dave", 1);
  // }

  const std::string package_path = ros::package::getPath("bolt_moveit");

  // Initialize main class
  bolt_moveit::BoltHilgendorf demo(hostname, package_path);

  // Shutdown
  ROS_INFO_STREAM_NAMED("main", "Shutting down.");
  ros::spinOnce();
  ros::Duration(2.0).sleep();
  ros::spinOnce();
  ros::shutdown();

  return 0;
}
