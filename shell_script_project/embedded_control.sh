#!/bin/bash
#
# ==========================================================
#   Embedded Device Simulation & Control System (x86)
#   Author: Pujit Kumar Cheel
#   Description:
#       Simulates sensors (Temp, Humidity, Light)
#       Controls actuators (Fan, LED, Dehumidifier)
#       Monitors system health (CPU, Memory, Disk)
#       Logs all readings into log file
# ==========================================================

LOG_FILE="./embedded_log.txt"
RUNNING=true

# ----------------- Sensor Simulation -----------------
get_sensors() {
    # Simulate sensor data (or read actual system metrics)
    temp=$((RANDOM % 100))         # Temperature in °C
    humidity=$((RANDOM % 100))     # Humidity in %
    light=$((RANDOM % 1000))       # Light intensity in Lux
}

# ----------------- System Health Monitoring -----------------
get_system_health() {
    cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print 100 - $8}')  # CPU usage %
    mem_usage=$(free | grep Mem | awk '{printf("%.2f"), $3/$2*100}') # Memory usage %
    disk_usage=$(df / | grep / | awk '{print $5}')                   # Disk usage %
}

# ----------------- Actuator Control -----------------
control_actuators() {
    # Default OFF
    fan_state="OFF"
    led_state="OFF"
    dehumidifier_state="OFF"

    # Control logic
    if [ "$temp" -gt 70 ]; then
        fan_state="ON"
    fi

    if [ "$light" -lt 200 ]; then
        led_state="ON"
    fi

    if [ "$humidity" -gt 80 ]; then
        dehumidifier_state="ON"
    fi
}

# ----------------- Logging -----------------
log_data() {
    timestamp=$(date "+%Y-%m-%d %H:%M:%S")
    echo "$timestamp | Temp: ${temp}°C | Humidity: ${humidity}% | Light: ${light} Lux | Fan: $fan_state | LED: $led_state | Dehumidifier: $dehumidifier_state" >> "$LOG_FILE"
}

# ----------------- Display Current Status -----------------
display_status() {
    clear
    echo "======================================================"
    echo "     EMBEDDED DEVICE CONTROL SYSTEM - SIMULATION"
    echo "======================================================"
    echo "Temperature      : ${temp}°C"
    echo "Humidity         : ${humidity}%"
    echo "Light Intensity  : ${light} Lux"
    echo
    echo "Fan State        : ${fan_state}"
    echo "LED State        : ${led_state}"
    echo "Dehumidifier     : ${dehumidifier_state}"
    echo
    echo "System CPU Usage : ${cpu_usage}%"
    echo "Memory Usage     : ${mem_usage}%"
    echo "Disk Usage       : ${disk_usage}"
    echo "------------------------------------------------------"
    echo "Press [Ctrl+C] to stop control loop"
}

# ----------------- Control Loop -----------------
start_control_loop() {
    echo "Starting control loop... Press Ctrl+C to stop."
    sleep 1
    trap "echo -e '\nStopping control loop...'; RUNNING=false" SIGINT

    while $RUNNING; do
        get_sensors
        get_system_health
        control_actuators
        log_data
        display_status
        sleep 2
    done
}

# ----------------- View Logs -----------------
view_logs() {
    echo "=============== SYSTEM LOGS ==============="
    if [ -f "$LOG_FILE" ]; then
        tail -n 20 "$LOG_FILE"
    else
        echo "No logs available yet."
    fi
    echo "==========================================="
    echo
    read -p "Press Enter to return to menu..."
}

# ----------------- Alert System -----------------
check_alerts() {
    if [ "$temp" -gt 90 ]; then
        echo "CRITICAL ALERT: Overheat detected!" | wall
    fi
}

# ----------------- Menu System -----------------
main_menu() {
    while true; do
        clear
        echo "=============================================="
        echo "   EMBEDDED DEVICE SIMULATION CONTROL MENU"
        echo "=============================================="
        echo "1. View Current Sensor Readings"
        echo "2. View System Health"
        echo "3. Start Control Loop"
        echo "4. View Logs"
        echo "5. Exit"
        echo "=============================================="
        read -p "Enter your choice: " choice

        case $choice in
            1)
                get_sensors
                control_actuators
                display_status
                read -p "Press Enter to return to menu..."
                ;;
            2)
                get_system_health
                echo "CPU Usage : ${cpu_usage}%"
                echo "Memory Usage : ${mem_usage}%"
                echo "Disk Usage : ${disk_usage}"
                read -p "Press Enter to return to menu..."
                ;;
            3)
                start_control_loop
                ;;
            4)
                view_logs
                ;;
            5)
                echo "Exiting system... Goodbye!"
                exit 0
                ;;
            *)
                echo "Invalid choice! Try again."
                sleep 1
                ;;
        esac
    done
}

# ----------------- Start Program -----------------
main_menu

