<!-- ABOUT THE PROJECT -->
## About The Project

this is a simple application that aimed at collecting data from tachimawari or dummy in real time and and then sending it to the arpis_client application using TCP

### Built With
* C++
* ROS2
* tachimawari
* arpis_network

## Getting Started
### Prerequisites
* ``` Make sured you have installed ROS2 foxy ```

### Installation
1. Clone tachimawari with its dependency, arpis_network in your `src` folder at ros2 workspace
2. check missing dependency 
    ```
    rosdep install -i --from-path src --rosdistro foxy
    ```
3. build this package and its dependencies
4. ``` source ./install/setup.zsh``` 

## Usage
ros2 run arpis_server arpis_main [mode] [args]

List available mode:
1. SDK
2. Dummy
3. CM740

List available args
1. `--addr [ip addr]`  
2. `--port [port]`

* you cant modify dummy array on `./src/arpis_server/joint/dummy/connector.cpp` at `void Dummy::load_data()`
