PIC32CM BACnet HVAC Heating Controller
Project Overview
This project is a prototype embedded HVAC heating controller built around the Microchip PIC32CM1216MC00032 microcontroller.

The controller is designed to:

measure room temperature using an MCP9808 digital temperature sensor over I2C;
compare the measured temperature with a configurable setpoint;
control an external heating request through a HEAT_CALL output;
expose HVAC configuration and runtime status through a BACnet-oriented object model;
provide an RS-485 communication layer intended for future BACnet MS/TP integration;
separate sensing, control, communication, and shared state using FreeRTOS tasks.

The project was developed as an embedded systems design exercise focused on HVAC control, firmware architecture, hardware interfaces, safety behavior, and BACnet-oriented communication design.


System Architecture
MCP9808 -> I2C -> SensorTask -> FreeRTOS Queue -> ControlTask -> HEAT_CALL

BACnetTask -> BACnet application layer -> HVAC shared state

          -> RS-485 driver -> SERCOM1 USART -> SN65HVD11

The shared HVAC state is protected by a FreeRTOS mutex and is used as the interface between the control logic and the communication layer.


Hardware Design
Microcontroller
The design uses the PIC32CM1216MC00032, an ARM Cortex-M0+ based MCU.

Main MCU interfaces used in the project:

SERCOM0 — I2C master for the MCP9808 temperature sensor;
SERCOM1 — USART for the RS-485 communication interface;
PA18 — RS485_DIR;
PA19 — HEAT_CALL;
PA30 / PA31 — SWD debug interface.
Power Architecture
The controller is intended for a 24 VDC HVAC environment.

24 VDC -> LM5164 Buck Converter -> 5 V -> MCP1825S-3302 -> 3.3 V

The 3.3 V rail powers the MCU, MCP9808, and RS-485 transceiver.
Temperature Sensor
The project uses the MCP9808 digital temperature sensor.

Configuration:

interface: I2C;
address: 0x18;
SDA: PA08;
SCL: PA09;
external pull-ups: approximately 4.7 kΩ;
local 100 nF decoupling.

The firmware reads the ambient-temperature register and converts the raw sensor value into degrees Celsius.
RS-485 Interface
The communication interface uses the SN65HVD11 half-duplex RS-485 transceiver.

PIC32CM TX  -> D

PIC32CM RX  <- R

PA18        -> DE + /RE

RS485_DIR controls communication direction:

LOW  = receive mode

HIGH = transmit mode

The driver waits until the final USART transmission is complete before returning the transceiver to receive mode.
Heating Output
HEAT_CALL is implemented as a low-side MOSFET output.

The output is intended to drive an external control input, relay, or SSR rather than directly powering a heater.

Fail-safe behavior keeps this output disabled during startup, invalid sensor conditions, and internal initialization failures.


Firmware Architecture
The firmware is divided into independent layers:

Application

├── SensorTask

├── ControlTask

├── BACnetTask

└── HVAC shared state

Drivers

├── MCP9808

└── RS-485

BACnet abstraction

├── BACnet objects

├── BACnet properties

├── BACnet device information

└── BACnet request handling

Generated platform layer

├── Harmony 3

├── SERCOM0 I2C

├── SERCOM1 USART

├── GPIO

└── FreeRTOS


FreeRTOS Tasks
SensorTask
Responsibilities:

initialize the MCP9808;
read room temperature periodically;
mark sensor data as valid or invalid;
publish the newest measurement to a FreeRTOS queue.

The sensor queue has a length of one and uses overwrite behavior because only the newest temperature measurement is required by the controller.
ControlTask
Responsibilities:

wait for new sensor data;
read the current HVAC configuration;
apply heating-enable and sensor-validity checks;
run the thermostat hysteresis algorithm;
control the HEAT_CALL output;
update the shared HVAC runtime status.

Default control values:

Setpoint:    22.0 °C

Hysteresis: ±0.5 °C

Example behavior:

Temperature <= 21.5 °C -> Heating ON

Temperature >= 22.5 °C -> Heating OFF

Inside the hysteresis band, the previous heating state is preserved.
BACnetTask
The BACnet task is currently used as the integration point for the BACnet application layer.

The project implements the BACnet-oriented object model and property access abstraction, but a complete BACnet MS/TP transport stack is intentionally outside the current project scope.

For a production device, a tested BACnet stack would be integrated with the existing RS-485 transport layer.


Shared HVAC State
Configuration and runtime status are kept in a shared module protected by a FreeRTOS mutex.
Configuration
typedef struct

{

    float setpoint_c;

    bool heating_enabled;

} HVAC_Config_t;
Runtime Status
typedef struct

{

    float room_temperature_c;

    bool sensor_valid;

    bool heat_call;

} HVAC_Status_t;

This separation allows the communication layer to change settings without directly modifying the control task.


Safety and Fail-Safe Behavior
The controller follows a fail-safe heating strategy.

Heating is disabled when:

the temperature sensor is invalid;
shared-state access fails;
heating is disabled by configuration;
startup initialization fails.

The HEAT_CALL output is explicitly placed in the OFF state during startup.

The communication layer does not directly control the MOSFET. Instead, external commands update HVAC configuration, while ControlTask remains responsible for all heating decisions.

This keeps safety and control logic centralized.


BACnet Object Model
The controller exposes the following logical BACnet objects:

Object
Instance
Name
Access
Analog Input
0
Room Temperature
Read only
Analog Value
0
Temperature Setpoint
Read / Write
Binary Output
0
Heating Enable
Read / Write
Binary Output
1
Heat Call
Read only
Binary Input
0
Sensor Fault
Read only

Room Temperature — AI:0
Maps to:

HVAC_Status_t.room_temperature_c

Represents the current temperature measured by the MCP9808.
Temperature Setpoint — AV:0
Maps to:

HVAC_Config_t.setpoint_c

The application layer validates setpoint writes before accepting them.

Current allowed range:

5 °C ... 35 °C
Heating Enable — BO:0
Maps to:

HVAC_Config_t.heating_enabled

Allows the HVAC control function to be enabled or disabled.
Heat Call — BO:1
Maps to:

HVAC_Status_t.heat_call

Represents the actual heating-demand state generated by ControlTask.
Sensor Fault — BI:0
Derived from:

!HVAC_Status_t.sensor_valid

Indicates whether the temperature sensor data is currently valid.


BACnet Property Layer
A generic property abstraction supports operations such as:

ReadProperty:

    object type

    object instance

    property

WriteProperty:

    object type

    object instance

    property

    value

Supported property abstractions include:

Present Value;
Object Name;
Description;
Units.

BACnet values are represented by a typed value structure supporting:

float;
bool;
string;
unsigned integer.

This keeps BACnet-facing code independent from the internal HVAC state representation.


BACnet Device Model
The project also defines a logical BACnet Device object.

Example configuration:

Device Instance: 1001

Object Name:     HVAC Heating Controller

Model Name:      PIC32CM BACnet Heating Controller

The device exposes an object list containing the HVAC AI, AV, BI, and BO objects implemented by the project.

The vendor information used in the demo is placeholder data and must be replaced with assigned production values in a real product.


RS-485 Driver
The RS-485 layer wraps the generated SERCOM1 USART peripheral.

Transmit flow:

Set RS485_DIR = TX

        |

Start USART transmission

        |

Wait for transfer completion

        |

Wait for final shift-register transmission

        |

Set RS485_DIR = RX

This avoids disabling the RS-485 transmitter before the final stop bit has left the UART.

The RS-485 driver is intentionally kept independent of BACnet so that the transport layer can be reused or replaced without modifying HVAC control logic.


Startup Sequence
The main startup sequence is:

SYS_Initialize()

      |

Set HEAT_CALL OFF

Set RS485 to RX

      |

Initialize HVAC state

      |

Create SensorTask

      |

Create ControlTask

      |

Create BACnetTask

      |

Run Harmony / FreeRTOS system tasks

If a critical initialization step fails, the controller remains in a safe state with heating disabled.


Development Environment
The project was developed using:

MPLAB X IDE;
MPLAB Code Configurator / Harmony 3;
XC32 Compiler 5.00;
FreeRTOS;
PIC32CM-MC Device Family Pack.

Configured peripherals include:

SERCOM0 I2C Master;
SERCOM1 USART;
GPIO;
FreeRTOS kernel.


Project Scope and Limitations
Implemented:

PIC32CM peripheral configuration;
MCP9808 temperature driver;
FreeRTOS-based sensor acquisition;
thermostat control logic;
shared synchronized HVAC state;
fail-safe heating behavior;
RS-485 transport driver;
BACnet-oriented object model;
BACnet property abstraction;
BACnet device/object-list abstraction;
BACnet-style request handling.

Intentionally not implemented:

full BACnet MS/TP framing;
token passing;
MS/TP MAC state machine;
BACnet MS/TP CRC handling;
full NPDU/APDU encoding and decoding;
BACnet network discovery on a live RS-485 network;
physical hardware validation of the final PCB.

For a production version, the intended next step would be integration of a proven BACnet stack with the existing RS-485 and application layers.


Example Functional Scenarios
Normal Heating
Setpoint = 22.0 °C

Temperature = 20.5 °C

Heating Enable = ON

Result:

HEAT_CALL = ON
Temperature Reached
Setpoint = 22.0 °C

Temperature = 22.8 °C

Result:

HEAT_CALL = OFF
Sensor Failure
Sensor Valid = false

Result:

HEAT_CALL = OFF

Sensor Fault = ACTIVE
Remote Setpoint Change
Current setpoint = 22.0 °C

BACnet application request:

AV:0 Present_Value = 23.0 °C

Result:

HVAC setpoint becomes 23.0 °C

ControlTask automatically uses the new value




Summary
The project demonstrates the design of a small embedded HVAC controller with clear separation between:

hardware drivers;
sensor acquisition;
control logic;
shared system state;
communication transport;
BACnet-oriented application objects.

The central design goal is to keep the heating-control logic independent from the communication protocol while providing a clean interface through which a future BACnet MS/TP stack can expose and modify HVAC data.
