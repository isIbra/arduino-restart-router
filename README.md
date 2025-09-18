# ESP32 Router Auto-Restart System

An Arduino-based system for ESP32 that automatically monitors internet connectivity and restarts your router when needed.

## Features

- **Automatic router restart** based on configurable time intervals
- **Internet connectivity monitoring** with automatic restart on connection failures
- **Configurable settings** for WiFi credentials, router access, and timing

## Hardware Requirements

- this was done mainly on the esp32 board, could be modified to work on similar wifi boards
- Stable power supply
- WiFi network access

## How It Works

1. base feature is a automatic restart with configs, i have a faulty router at my farm, so i had this help me restart it every once in a while
2. network health montoring
3. restart based on failed network calls

## Serial Output

The system provides detailed logging including:

- System configuration on startup
- WiFi connection status and signal strength
- Internet connectivity check results
- Router restart attempts and results
- Periodic status updates with uptime and statistics

## Router Compatibility

The restart functionality is designed for routers running OpenWrt with LuCI web interface. For other router types, you may need to modify the `restartRouter()` function to match your router's API endpoints.
