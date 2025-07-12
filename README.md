# Smart-barrier
This project implements an automatic barrier system that detects the presence of a vehicle or obstacle using an ultrasonic sensor, and controls a servo motor to open or close the gate. It is built around an Arduino microcontroller, with code developed in Atmel Studio using hardware timers for precise servo control.

A Proteus simulation file is included, along with the compiled .hex file, to allow testing the system virtually without hardware.

🛠️ Features
🧠 Obstacle detection using ultrasonic distance sensor (HC-SR04)

🔄 Automated servo control for barrier movement

⏱️ Precise timing using hardware timers (no delay blocking)

💻 Code written in C with Atmel Studio

🧪 Proteus simulation project included with .hex ready to run



🚀 Getting Started
▶️ Run the Simulation (Proteus)
Open Proteus simulation files/simulation proteus.pdsprj with Proteus 8 or higher.

The Arduino UNO should already be configured with the projet_info.hex file.

Click Play ▶️ to run the simulation.

Use a virtual object (or your cursor in proximity mode) to trigger the ultrasonic sensor and observe the barrier opening/closing.

🧑‍💻 Compile the Code (Optional)
If you want to modify and compile the code yourself:

Open src/main.c in Atmel Studio.

Select the correct microcontroller (usually ATmega328P).

Build the project to generate a new .hex file.

Replace the existing one in Proteus if needed.

📌 Requirements
Atmel Studio (for code editing and compilation)

Proteus (for circuit simulation)

Basic knowledge of microcontroller programming and timer modules

📄 License
This project is licensed under the MIT License.
Feel free to use, modify, and share it.

🤝 Contributing
Pull requests and suggestions are welcome!
If you have improvements, fixes, or enhancements, don't hesitate to submit them.
