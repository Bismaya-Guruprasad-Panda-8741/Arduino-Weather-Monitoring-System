# Arduino-Weather-Monitoring-System
🌱 A beginner-friendly weather station built with Arduino! Monitor temperature, humidity, rainfall, and air quality in real time — all displayed on an LCD screen. Perfect for your first IoT or electronics project. No experience needed — just follow the wiring guide and you're good to go! 🚀
..
.
.
.
# 🌦️ Weather Monitoring System — Arduino

> A complete weather monitoring station using **DHT11**, **Rain Sensor (MH-RD)**, **MQ135**, and an **I2C LCD** — all powered by Arduino!

---

## 📋 Table of Contents

- [📦 Components Required](#-components-required)
- [🔌 Wiring & Connections](#-wiring--connections)
- [🛠️ Step-by-Step Setup](#️-step-by-step-setup)
- [📚 Libraries to Install](#-libraries-to-install)
- [🚀 Upload & Run](#-upload--run)
- [📺 LCD Display Screens](#-lcd-display-screens)
- [📡 Serial Monitor Output](#-serial-monitor-output)
- [⚙️ How It Works](#️-how-it-works)
- [🐛 Troubleshooting](#-troubleshooting)
- [📁 Project Structure](#-project-structure)

---

## 📦 Components Required

| # | Component | Quantity |
|---|-----------|----------|
| 1 | 🟦 Arduino Uno / Nano | 1 |
| 2 | 🌡️ DHT11 Temperature & Humidity Sensor | 1 |
| 3 | 🌧️ Rain Sensor Module (DSK MH-RD) | 1 |
| 4 | 🌫️ MQ135 Air Quality Sensor | 1 |
| 5 | 🖥️ I2C LCD Display (16×2, 4-pin: VCC GND SDA SCL) | 1 |
| 6 | 🔌 Jumper Wires (Male-to-Male & Male-to-Female) | ~20 |
| 7 | 🍞 Breadboard (optional) | 1 |
| 8 | 🔋 USB Cable or 5V Power Supply | 1 |

---

## 🔌 Wiring & Connections

### 🌡️ DHT11 Sensor → Arduino

| DHT11 Pin | Arduino Pin |
|-----------|-------------|
| VCC       | 5V          |
| GND       | GND         |
| DATA      | D2          |

> ⚠️ Some DHT11 modules need a **10kΩ pull-up resistor** between VCC and DATA. Breakout modules usually have it built-in.

---

### 🌧️ Rain Sensor Module (DSK MH-RD) → Arduino

| Rain Module Pin | Arduino Pin |
|-----------------|-------------|
| VCC             | 5V          |
| GND             | GND         |
| DO (Digital Out)| D3          |
| AO (Analog Out) | A0          |

> 💡 Turn the **blue potentiometer** on the module to set the rain detection sensitivity threshold.

---

### 🌫️ MQ135 Air Quality Sensor → Arduino

| MQ135 Pin | Arduino Pin |
|-----------|-------------|
| VCC       | 5V          |
| GND       | GND         |
| DO        | D4          |
| AO        | A1          |

> ⚠️ MQ135 requires a **warm-up time of ~2 minutes** after power-on for accurate readings.

---

### 🖥️ I2C LCD (16×2, 4-pin) → Arduino

| LCD Pin | Arduino Pin |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| SDA     | A4          |
| SCL     | A5          |

> 🔍 Default I2C address is **0x27**. If LCD doesn't show anything, try `0x3F`. Use an I2C scanner sketch to detect the correct address.

---

### 🗺️ Full Wiring Summary

```
Arduino 5V  ──── DHT11 VCC, Rain VCC, MQ135 VCC, LCD VCC
Arduino GND ──── DHT11 GND, Rain GND, MQ135 GND, LCD GND
Arduino D2  ──── DHT11 DATA
Arduino D3  ──── Rain Module DO
Arduino D4  ──── MQ135 DO
Arduino A0  ──── Rain Module AO
Arduino A1  ──── MQ135 AO
Arduino A4  ──── LCD SDA
Arduino A5  ──── LCD SCL
```

---

## 🛠️ Step-by-Step Setup

### Step 1 — Install Arduino IDE
- Download from: https://www.arduino.cc/en/software
- Install and open the IDE

### Step 2 — Install Required Libraries
Open Arduino IDE → **Sketch → Include Library → Manage Libraries**

Search and install:
- ✅ `DHT sensor library` by **Adafruit**
- ✅ `Adafruit Unified Sensor` by **Adafruit**
- ✅ `LiquidCrystal I2C` by **Frank de Brabander**

### Step 3 — Connect the Hardware
Follow the wiring table above. Double-check power (5V/GND) connections before powering on.

### Step 4 — Open the Sketch
Open `src/weather_monitor.ino` in Arduino IDE.

### Step 5 — Select Board & Port
- **Tools → Board → Arduino Uno** (or Nano if applicable)
- **Tools → Port → COMX** (Windows) or `/dev/ttyUSBx` (Linux/Mac)

### Step 6 — Upload the Code
Click the **➡️ Upload** button. Wait for "Done uploading."

### Step 7 — Check LCD & Serial Monitor
- LCD should display weather data alternating every 3 seconds
- Open **Serial Monitor** (Ctrl+Shift+M) at **9600 baud** to view detailed logs

---

## 📚 Libraries to Install

```
Library Name              | Author
--------------------------|---------------------------
DHT sensor library        | Adafruit
Adafruit Unified Sensor   | Adafruit
LiquidCrystal I2C         | Frank de Brabander
Wire (built-in)           | Arduino
```

---

## 🚀 Upload & Run

```bash
1. Connect Arduino to PC via USB
2. Open weather_monitor.ino in Arduino IDE
3. Select correct Board and Port
4. Click Upload (→)
5. Open Serial Monitor at 9600 baud
```

---

## 📺 LCD Display Screens

The LCD alternates between **two screens** every 3 seconds:

**Screen 1 — Temperature, Humidity & Rain**
```
T:28.5°C H:65%
Rain:YES 72%
```

**Screen 2 — Air Quality**
```
Air Quality:
Moderate 45%
```

---

## 📡 Serial Monitor Output

```
=============================
Temperature : 28.50 C
Humidity    : 65 %
Rain        : YES
Rain Level  : 72 %
Gas Raw     : 462
Gas Level   : 45 %
Air Status  : Moderate
=============================
```

---

## ⚙️ How It Works

| Sensor | What It Measures | Output Used |
|--------|-----------------|-------------|
| 🌡️ DHT11 | Temperature (°C) & Humidity (%) | Digital DATA pin |
| 🌧️ MH-RD Rain | Rain presence & intensity | DO (digital) + AO (analog) |
| 🌫️ MQ135 | Air/gas quality (CO₂, NH₃, smoke) | DO (digital) + AO (analog) |
| 🖥️ LCD I2C | Display all readings | I2C (SDA/SCL) |

### 🌫️ Air Quality Scale
| Gas % | Status |
|-------|--------|
| 0–29% | ✅ Clean |
| 30–59% | ⚠️ Moderate |
| 60–100% | 🚨 Danger |

### 🌧️ Rain Scale
| DO Pin | Status |
|--------|--------|
| LOW    | 🌧️ Rain Detected |
| HIGH   | ☀️ No Rain |

---

## 🐛 Troubleshooting

| Problem | Possible Fix |
|---------|-------------|
| LCD shows nothing | Check I2C address — try `0x3F` instead of `0x27` |
| LCD shows blocks | Adjust contrast potentiometer on I2C module |
| DHT11 shows `nan` | Check wiring; add 10kΩ pull-up on DATA pin |
| MQ135 readings unstable | Wait 2–5 min warm-up time after power-on |
| Rain sensor always ON | Adjust the blue potentiometer on MH-RD module |
| Upload fails | Check correct COM port is selected |

---

## 📁 Project Structure

```
weather_monitoring_arduino/
│
├── src/
│   └── weather_monitor.ino    # Main Arduino sketch
│
├── README.md                  # This file
└── LICENSE                    # MIT License
```

---

## 📜 License

This project is licensed under the **MIT License** — free to use, modify, and distribute! 🎉

---

## 🙌 Credits

Built with ❤️ using:
- [Arduino](https://www.arduino.cc/)
- [Adafruit DHT Library](https://github.com/adafruit/DHT-sensor-library)
- [LiquidCrystal I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C)

---

> ⭐ If you found this helpful, give the repo a star on GitHub!
