# First assignment

To make this run in gazebo with the 'Welcome to Wayne's World!' print:
```
cd project1/build
cmake ../
make
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:`pwd`
gazebo ../world/project1_world
```