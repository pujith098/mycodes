# 🟢 Embedded Device Simulation & Control System (Shell Script)


**Embedded Device Simulation & Control System** is a **bash shell script** that simulates an embedded control system on an x86 Linux laptop.  
It demonstrates **sensor simulation, actuator control, system health monitoring, logging**, and an **interactive menu interface**.

---

## 🚀 Features

- Sensor Simulation: Temperature, Humidity, Light intensity  
- Actuator Control: Fan, LED, Dehumidifier based on sensor thresholds  
- System Health Monitoring: CPU, Memory, Disk usage  
- Real-time Control Loop: Updates every 2 seconds  
- Logging: Timestamped logs in `embedded_log.txt`  
- Menu-driven Interface: Interactive and user-friendly  

---

## 📂 Menu after script running

1. View Current Sensor Readings
2. View System Health
3. Start Control Loop
4. View Logs
5. Exit

Option 1: Shows current sensor readings and actuator states

Option 2: Displays CPU, memory, and disk usage

Option 3: Starts the real-time control loop

Option 4: Shows last 20 log entries

Option 5: Exits the program

During the control loop, press Ctrl+C to stop safely

## **File:** `embedded_log.txt`

- This is **auto-generated** when you run the script.  
- Initially, you can create an **empty file**:

touch embedded_log.txt

## Make the script executable:

chmod +x embedded_control.sh

## Run the script:

./embedded_control.sh

