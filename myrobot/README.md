# First assignment

To make this run in gazebo with the 'Hello world!' print:
```
cd myrobot/build
cmake ../
make
export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:`pwd`
gazebo ../world/myworld
```