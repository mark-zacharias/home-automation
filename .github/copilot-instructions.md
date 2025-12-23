# Home Automation Copilot Instructions

## Project Overview
This is a home automation codebase focused on ESP8266-based IoT devices, primarily using LoRa wireless communication for car warming control and basic ESP8266 projects. The goal is offline-first automation integrated with Home Assistant.

## Coding Standards
Use tabs not spaces.

## Architecture & Key Components

### ESP8266 + LoRa Communication Pattern
- **Primary use case**: Car warmer control via LoRa devices (house controller ↔ car device)
- **Standard hardware**: Wemos D1 Mini (ESP8266) + SX1276/77/78/79 LoRa modules
- **Communication**: 915MHz LoRa (North America), range-optimized settings

### Project Structure
```
/blink-test/          - Basic ESP8266 development/testing
/lora-test/
  /lora_send/         - LoRa transmitter (sender device)
  /lora_receive/      - LoRa receiver (monitoring device)
/on-air/              - WiFi-connected devices (ThingSpeak integration)
```

## Development Workflow

### LoRa Configuration Pattern
Standard range-optimized settings used across all LoRa devices:
```cpp
LoRa.setSyncWord(0x34);          // Match between sender/receiver
LoRa.setSpreadingFactor(12);     // Max range (6-12 scale)
LoRa.setSignalBandwidth(125E3);  // Lower = more range, less speed
LoRa.setCodingRate4(8);          // Higher = more range, less speed
LoRa.enableCrc();                // Reliability over speed
```

## Code Patterns

### Device Initialization Pattern
All ESP8266 projects follow this setup sequence:
1. Serial.begin() with appropriate baud rate
2. 500ms delay for ESP8266 boot stability
3. Pin configuration (LED_BUILTIN for status indication)
4. Device-specific initialization (LoRa.begin(), WiFi.begin())
5. Configuration of device parameters
6. "Setup complete" debug message

### LED Status Indication
- **Built-in LED**: Used for visual debugging in all projects
- **LoRa projects**: LED flashes on packet send/receive
- **WiFi projects**: LED indicates connection status


## Key Files to Reference
- `/lora-test/lora_send/src/main.cpp` - Standard LoRa transmitter pattern
- `/lora-test/lora_receive/src/main.cpp` - Standard LoRa receiver pattern  
- `/blink-test/src/main.cpp` - Basic ESP8266 development template
- `/read.md` - Project goals and future roadmap
