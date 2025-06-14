# Purpose
The purpose of this repository/training course is to build a foundational understanding and skills for GNC topics 
including data acquisition and filtering, fusion algorithms, basic system controllers, and then touching on more realistic and 
advanced system controllers.

# Control Systems Training Outline
## **Phase 1: Foundations**

### **Lesson 1: Reading Sensor Data**
- **Purpose:** Learn to acquire raw accelerometer data from the Pixhawk and visualize it in MATLAB.
- **Focus:** Connection setup, basic data sampling, and visualization.

### **Lesson 2: Simple Data Filtering**
- **Purpose:** Introduce filtering methods (e.g., moving average) to reduce noise and understand the impact of noise on data.
- **Focus:** Compare raw vs. filtered data and understand why filtering is crucial.

### **Lesson 3: Gyroscope Integration**
- **Purpose:** Extend to gyroscope data to understand rotational velocity and its relationship with accelerometer data.
- **Focus:** Data acquisition and logging for multi-sensor systems.

### **Lesson 4: Complementary Filter**
- **Purpose:** Combine accelerometer and gyroscope data to estimate orientation with a simple sensor fusion technique.
- **Focus:** Practical introduction to basic sensor fusion concepts.

### **Lesson 5: Introduction to Kalman Filtering**
- **Purpose:** Implement a basic Kalman filter for 1D data to understand state estimation and uncertainty reduction.
- **Focus:** Step-by-step breakdown of Kalman filter theory and implementation.

## **Phase 2: Control Systems**

### **Lesson 6: Simulink Basics**
- **Purpose:** Familiarize with Simulink and model simple physical systems like a mass-spring-damper.
- **Focus:** Basic modeling, simulation setup, and visualization in Simulink.

### **Lesson 7: Implementing a PID Controller**
- **Purpose:** Build a PID controller in MATLAB and Simulink to control a simulated system.
- **Focus:** Understanding PID tuning parameters and their effect on system behavior.

### **Lesson 8: Pixhawk PID Loop**
- **Purpose:** Implement a PID controller on the Pixhawk for controlling a simple simulated or real system.
- **Focus:** Transitioning from simulation to hardware-in-the-loop (HITL).

## **Phase 3: Advanced Topics**

### **Lesson 9: Extended Kalman Filter (EKF)**
- **Purpose:** Implement an EKF for attitude estimation using accelerometer and gyroscope data.
- **Focus:** Multi-dimensional Kalman filtering and advanced sensor fusion.

### **Lesson 10: System Identification**
- **Purpose:** Model a physical system by analyzing input-output data using system identification techniques.
- **Focus:** Building accurate models for control design.

### **Lesson 11: Sensor Fusion Algorithms**
- **Purpose:** Explore and compare advanced sensor fusion algorithms (e.g., Madgwick, Mahony).
- **Focus:** Implement and evaluate algorithms for orientation estimation.

### **Lesson 12: Simulating a Control System with HITL**
- **Purpose:** Integrate sensor fusion and control in a hardware-in-the-loop setup with Pixhawk and Simulink.
- **Focus:** Bridging simulation and hardware for real-world applications.

## **Phase 4: Advanced Applications**

### **Lesson 13: 2D Control Systems**
- **Purpose:** Simulate a 2D control system (e.g., a planar pendulum) using sensor fusion and PID.
- **Focus:** Multi-axis control and enhanced visualization.

### **Lesson 14: Multiple Input Single Output (MISO) Systems**
- **Purpose:** Model and control systems with multiple inputs and a single output, such as balancing forces from different actuators.
- **Focus:** Practical handling of MISO systems in MATLAB and Simulink.

### **Lesson 15: Coupled Systems**
- **Purpose:** Analyze and control systems with coupled dynamics (e.g., two masses connected by a spring).
- **Focus:** Advanced modeling and simulation techniques.

### **Lesson 16: Nonlinear Systems**
- **Purpose:** Explore the challenges of controlling nonlinear systems, such as systems with friction or saturation.
- **Focus:** Understanding limitations of linear control methods and introducing nonlinear approaches.

### **Lesson 17: Model Predictive Control (MPC)**
- **Purpose:** Introduce model predictive control and its application to advanced control problems.
- **Focus:** Learn to anticipate future states and optimize control inputs.
