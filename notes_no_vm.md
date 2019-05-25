# Doing the Robotics Software Engineer Nanodegree from a linux machine (no VM or workspace)

## Characteristics
- Ubuntu 18.04.2 LTS
- ROS version ?
- Gazebo version ?

## Tips
Always run `sudo apt-get update && sudo apt-get upgrade -y`
I can recommend Visual Studio Code, easily used for multiple programming and scripting languages in the same project/folder.


## Errors handled/solved/worked around
- Gazebo giving error:
  `[Err] [REST.cc:205] Error in REST request`
  Solution described [here](https://bitbucket.org/osrf/gazebo/issues/2607/error-restcc-205-during-startup-gazebo)
- Gazebo bug/missing functionality:
    Interesting find, you cannot edit existing/saved buildings. Some aspects are changeable but not much.
- rviz didnt show any models except the meshed LIDAR, see [here] (https://answers.ros.org/question/296227/robot-model-does-not-appear-in-rviz-melodic/) and [here] (https://github.com/ros-visualization/rviz/issues/1249). TL/DR: `export LC_NUMERIC="en_US.UTF-8"` worked for me. Colors are not completely ok though. Update: looks like the red is some kind of highlighting.