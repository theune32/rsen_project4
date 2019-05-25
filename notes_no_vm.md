# Doing the Robotics Software Engineer Nanodegree from a linux machine (no VM or workspace)

## Characteristics
- Ubuntu 18.04.2 LTS
- ROS version ?
- Gazebo version ?

## Tips
Always run `sudo apt-get update && sudo apt-get upgrade -y`.
I can recommend Visual Studio Code, easily used for multiple programming and scripting languages in the same project/folder.
There is a setup page available [here](http://wiki.ros.org/IDEs#Visual_Studio_Code_.28VSCode.29). There still was an issue with the right include.
Manually changing the file `.vscode/c_cpp_properties.json` by adding `/opt/ros/melodic/**` to the `INCLUDE_PATH`, solved the issue.
An helpful link for setting up ros node classes is found [here](https://github.com/wsnewman/ros_class/blob/master/example_ros_class/src/example_ros_class.cpp).




## Errors handled/solved/worked around
- Gazebo giving error:
  `[Err] [REST.cc:205] Error in REST request`
  Solution described [here](https://bitbucket.org/osrf/gazebo/issues/2607/error-restcc-205-during-startup-gazebo)
- Gazebo bug/missing functionality:
    Interesting find, you cannot edit existing/saved buildings. Some aspects are changeable but not much.

