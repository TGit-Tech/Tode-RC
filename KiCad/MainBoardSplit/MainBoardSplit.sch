EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x07_Female J3
U 1 1 5E38FFA6
P 5350 1500
F 0 "J3" V 5422 1480 50  0000 C CNN
F 1 "E32" V 5513 1480 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 5350 1500 50  0001 C CNN
F 3 "~" H 5350 1500 50  0001 C CNN
	1    5350 1500
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x08_Female J4
U 1 1 5E39008F
P 2900 4250
F 0 "J4" V 2750 4750 50  0000 C CNN
F 1 "GMT177" V 2850 4750 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 2900 4250 50  0001 C CNN
F 3 "~" H 2900 4250 50  0001 C CNN
	1    2900 4250
	0    -1   1    0   
$EndComp
Text Label 5350 1950 1    50   ~ 0
RXD1
Text Label 5450 1950 1    50   ~ 0
TXD1
$Comp
L power:GNDREF #PWR0101
U 1 1 5E390558
P 2100 5000
F 0 "#PWR0101" H 2100 4750 50  0001 C CNN
F 1 "GNDREF" H 2105 4827 50  0000 C CNN
F 2 "" H 2100 5000 50  0001 C CNN
F 3 "" H 2100 5000 50  0001 C CNN
	1    2100 5000
	1    0    0    -1  
$EndComp
Text Label 2600 4000 1    50   ~ 0
GND
Text Label 2700 4000 1    50   ~ 0
VCC
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J2
U 1 1 5E3A1FAC
P 2600 2500
F 0 "J2" V 2600 2200 50  0000 L CNN
F 1 "ICSP" V 2700 2150 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 2600 2500 50  0001 C CNN
F 3 "~" H 2600 2500 50  0001 C CNN
	1    2600 2500
	0    1    1    0   
$EndComp
Text Label 5250 1950 1    50   ~ 0
AUX
Text Label 5550 1950 1    50   ~ 0
M1
Text Label 5650 1950 1    50   ~ 0
M0
Text Label 2800 4000 1    50   ~ 0
SCK
Text Label 2900 4000 1    50   ~ 0
SDA
Text Label 3000 4000 1    50   ~ 0
RES
Text Label 3100 4000 1    50   ~ 0
RS
Text Label 3200 4000 1    50   ~ 0
CS
$Comp
L Connector_Generic:Conn_02x03_Counter_Clockwise J5
U 1 1 5E3C4F6E
P 3950 3000
F 0 "J5" H 4050 2800 50  0000 R CNN
F 1 "D44-49" H 4150 3200 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 3950 3000 50  0001 C CNN
F 3 "~" H 3950 3000 50  0001 C CNN
	1    3950 3000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5E3CCC76
P 3300 3750
F 0 "R1" V 3300 3750 50  0000 C CNN
F 1 "39" V 3184 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3230 3750 50  0001 C CNN
F 3 "~" H 3300 3750 50  0001 C CNN
	1    3300 3750
	-1   0    0    1   
$EndComp
Text Label 3300 4000 1    50   ~ 0
BL
Text Label 3300 3500 1    50   ~ 0
BL2
Wire Wire Line
	2900 3450 2600 3450
Wire Wire Line
	3300 4050 3300 3900
Connection ~ 2100 3700
Wire Wire Line
	5150 1700 5150 2100
Text Notes 4300 3100 2    50   ~ 0
D46
Text Notes 4300 3000 2    50   ~ 0
D44
Text Notes 4300 2900 2    50   ~ 0
D47
Text Notes 3600 2900 2    50   ~ 0
D45
Text Notes 3600 3000 2    50   ~ 0
D48
Text Notes 3600 3100 2    50   ~ 0
D49
Text Notes 2250 3600 0    50   ~ 0
VCC
Text Notes 2400 3700 2    50   ~ 0
GND
Text Notes 5050 1950 1    50   ~ 0
GND
Text Notes 5150 1950 1    50   ~ 0
VCC
Wire Wire Line
	5050 1700 5050 2000
Wire Wire Line
	2900 4050 2900 3450
Wire Wire Line
	2700 4050 2700 3600
Wire Wire Line
	2600 4050 2600 3700
Wire Wire Line
	5050 2000 2100 2000
Wire Wire Line
	2100 2000 2100 2950
Wire Wire Line
	2150 2100 5150 2100
Wire Wire Line
	3000 2200 2500 2200
Wire Wire Line
	2500 2200 2500 2300
Wire Wire Line
	3000 2200 3000 4050
Wire Wire Line
	2800 2250 2600 2250
Wire Wire Line
	2600 2250 2600 2300
Wire Wire Line
	2800 2250 2800 4050
NoConn ~ 2700 2300
Wire Wire Line
	2600 2800 2600 3450
Wire Wire Line
	5650 1700 5650 2250
Wire Wire Line
	5550 1700 5550 2350
Wire Wire Line
	4150 3000 4400 3000
Wire Wire Line
	4150 2900 4450 2900
Wire Wire Line
	4400 3000 4400 3450
Wire Wire Line
	4400 3450 3300 3450
Wire Wire Line
	2500 2800 2500 2950
Wire Wire Line
	2500 2950 2100 2950
Connection ~ 2100 2950
Wire Wire Line
	2100 2950 2100 3700
Wire Wire Line
	2700 2800 2700 3050
Wire Wire Line
	2150 2100 2150 3050
Wire Wire Line
	3300 3450 3300 3600
$Comp
L Device:R R3
U 1 1 5F9F15DB
P 6150 2300
F 0 "R3" V 5943 2300 50  0000 C CNN
F 1 "R" V 6034 2300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 2300 50  0001 C CNN
F 3 "~" H 6150 2300 50  0001 C CNN
	1    6150 2300
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5F9F1A2F
P 6150 2000
F 0 "R2" V 5943 2000 50  0000 C CNN
F 1 "R" V 6034 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6080 2000 50  0001 C CNN
F 3 "~" H 6150 2000 50  0001 C CNN
	1    6150 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 5000 2100 4600
Wire Wire Line
	2100 3700 2600 3700
Wire Wire Line
	2600 4600 2100 4600
Wire Wire Line
	2600 4600 2600 4800
Connection ~ 2100 4600
Text Label 5800 2150 0    50   ~ 0
Vmon
Text Label 3000 4550 0    50   ~ 0
Akb
Text Label 5900 2300 0    50   ~ 0
VIN
$Comp
L Connector:Conn_01x05_Male J9
U 1 1 5F9E3CF4
P 6200 2700
F 0 "J9" H 6172 2632 50  0000 R CNN
F 1 "WIRES" H 6172 2723 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6200 2700 50  0001 C CNN
F 3 "~" H 6200 2700 50  0001 C CNN
	1    6200 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	5050 2000 6000 2000
Connection ~ 5050 2000
Wire Wire Line
	6300 2000 6300 2150
Connection ~ 6300 2150
Wire Wire Line
	6300 2150 6300 2300
Wire Wire Line
	6000 2300 5850 2300
Wire Wire Line
	5750 2150 6300 2150
Wire Wire Line
	2100 3700 2100 4600
Wire Wire Line
	2150 3600 2150 3050
Connection ~ 2150 3050
Wire Wire Line
	2150 3600 2700 3600
Wire Wire Line
	2150 3050 2700 3050
Wire Wire Line
	2800 4800 2800 4550
Wire Wire Line
	2800 4550 5500 4550
Wire Wire Line
	2700 4800 2700 4500
Wire Wire Line
	2700 4500 2150 4500
Wire Wire Line
	2150 4500 2150 3600
Connection ~ 2150 3600
Wire Wire Line
	4150 3100 5250 3100
Wire Wire Line
	5250 1700 5250 3100
Wire Wire Line
	3150 2250 5650 2250
Wire Wire Line
	3150 2250 3150 3000
Wire Wire Line
	5550 2350 4450 2350
Wire Wire Line
	4450 2350 4450 2900
Wire Wire Line
	5500 2900 5500 4550
Wire Wire Line
	5500 2900 6000 2900
$Comp
L Connector:Conn_01x03_Female J1
U 1 1 5FA5CCFB
P 2700 5000
F 0 "J1" V 2546 4812 50  0000 R CNN
F 1 "KEYB" V 2637 4812 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 2700 5000 50  0001 C CNN
F 3 "~" H 2700 5000 50  0001 C CNN
	1    2700 5000
	0    -1   1    0   
$EndComp
Wire Wire Line
	5350 1700 5350 2800
Wire Wire Line
	5350 2800 6000 2800
Wire Wire Line
	5750 2150 5750 2600
Wire Wire Line
	5850 2300 5850 2500
Wire Wire Line
	6000 2500 5850 2500
Wire Wire Line
	6000 2600 5750 2600
Wire Wire Line
	5450 2700 6000 2700
Wire Wire Line
	5450 1700 5450 2700
Wire Wire Line
	3100 2900 3100 4050
Wire Wire Line
	3650 3000 3150 3000
Wire Wire Line
	3100 2900 3650 2900
Wire Wire Line
	3650 3100 3200 3100
Wire Wire Line
	3200 3100 3200 4050
$EndSCHEMATC