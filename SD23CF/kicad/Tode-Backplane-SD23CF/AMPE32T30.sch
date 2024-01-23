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
L Connector_Generic:Conn_02x03_Odd_Even J1
U 1 1 5FA650BC
P 4100 1100
F 0 "J1" H 4150 1417 50  0000 C CNN
F 1 "PWR" H 4150 1326 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Vertical" H 4100 1100 50  0001 C CNN
F 3 "~" H 4100 1100 50  0001 C CNN
	1    4100 1100
	-1   0    0    -1  
$EndComp
Text Label 4450 1000 0    50   ~ 0
VIN
Text Label 4450 1100 0    50   ~ 0
GND
Text Label 4450 1200 0    50   ~ 0
5V
$Comp
L Connector_Generic:Conn_01x07 J4
U 1 1 5FA69381
P 5500 4150
F 0 "J4" V 5600 4200 50  0000 R CNN
F 1 "E32" V 5600 4050 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 5500 4150 50  0001 C CNN
F 3 "~" H 5500 4150 50  0001 C CNN
	1    5500 4150
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5FA83DE8
P 4950 1150
F 0 "R1" V 4745 1150 50  0000 C CNN
F 1 "910K" V 4836 1150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4950 1150 50  0001 C CNN
F 3 "~" H 4950 1150 50  0001 C CNN
	1    4950 1150
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 5FA8D74B
P 5100 5050
F 0 "R3" V 5200 5050 50  0000 C CNN
F 1 "39" V 5300 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5100 5050 50  0001 C CNN
F 3 "~" H 5100 5050 50  0001 C CNN
	1    5100 5050
	0    1    1    0   
$EndComp
Text Label 4100 5000 3    50   ~ 0
SDA
Text Label 4200 5150 1    50   ~ 0
RES
Text Label 4300 5150 1    50   ~ 0
RS
Text Label 4400 5150 1    50   ~ 0
CS
Text Label 4500 5150 1    50   ~ 0
BL
Text Label 4000 5150 1    50   ~ 0
SCK
Text Label 5150 1350 0    50   ~ 0
Vmon
Text Label 5800 3850 1    50   ~ 0
M0
Text Label 5700 3850 1    50   ~ 0
M1
Text Label 5600 3850 1    50   ~ 0
TXD
Text Label 5500 3850 1    50   ~ 0
RXD
Text Label 5400 3850 1    50   ~ 0
AUX
$Comp
L Connector_Generic:Conn_01x02 J9
U 1 1 5FAA8A1D
P 5700 1000
F 0 "J9" H 5780 992 50  0000 L CNN
F 1 "Batt" H 5780 901 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x02_P4.6mm_D0.9mm_OD2.1mm" H 5700 1000 50  0001 C CNN
F 3 "~" H 5700 1000 50  0001 C CNN
	1    5700 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 5FA843F7
P 4950 1550
F 0 "R2" V 4745 1550 50  0000 C CNN
F 1 "470K" V 4836 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4950 1550 50  0001 C CNN
F 3 "~" H 4950 1550 50  0001 C CNN
	1    4950 1550
	-1   0    0    1   
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5FA7B97D
P 5600 5400
F 0 "BZ1" H 5752 5429 50  0000 L CNN
F 1 "Buzzer" H 5752 5338 50  0000 L CNN
F 2 "Buzzer_Beeper:MagneticBuzzer_PUI_AT-0927-TT-6-R" V 5575 5500 50  0001 C CNN
F 3 "~" V 5575 5500 50  0001 C CNN
	1    5600 5400
	1    0    0    -1  
$EndComp
Text Label 5600 4800 2    50   ~ 0
BZ
$Comp
L Connector_Generic:Conn_01x10 J11
U 1 1 5FB2363E
P 4500 2050
F 0 "J11" H 4650 2600 50  0000 C CNN
F 1 "IO" H 4650 2500 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 4500 2050 50  0001 C CNN
F 3 "~" H 4500 2050 50  0001 C CNN
	1    4500 2050
	-1   0    0    -1  
$EndComp
Text Label 5450 1850 2    50   ~ 0
A1
Text Label 5450 1950 2    50   ~ 0
A3
Text Label 5450 2050 2    50   ~ 0
A5
Text Label 5450 2150 2    50   ~ 0
A7
Text Label 5450 2250 2    50   ~ 0
A9
Text Label 5450 2350 2    50   ~ 0
A11
Text Label 5450 2450 2    50   ~ 0
A13
Text Label 5900 3300 3    50   ~ 0
D45
Text Label 6000 3300 3    50   ~ 0
BLR
Wire Wire Line
	3800 1000 4300 1000
Wire Wire Line
	3800 1100 4300 1100
Connection ~ 4300 1000
Wire Wire Line
	3800 1200 4300 1200
Connection ~ 4300 1200
Wire Wire Line
	4300 1200 4700 1200
Wire Wire Line
	4300 1100 4800 1100
Connection ~ 4300 1100
Wire Wire Line
	4300 1000 4950 1000
Text Notes 4450 3400 0    50   ~ 0
D23
Text Notes 4450 3300 0    50   ~ 0
D21
Text Notes 4450 3200 0    50   ~ 0
D19
Text Notes 5100 3200 0    50   ~ 0
D18
Text Notes 5100 3300 0    50   ~ 0
D20
Text Notes 5100 3400 0    50   ~ 0
D22
Wire Wire Line
	5500 1850 4700 1850
Wire Wire Line
	5500 1950 4700 1950
Wire Wire Line
	5500 2050 4700 2050
Wire Wire Line
	5500 2150 4700 2150
Wire Wire Line
	4700 1750 4800 1750
Wire Wire Line
	4700 1650 4700 1350
Wire Wire Line
	4800 1100 4800 1300
Wire Wire Line
	4950 1050 4950 1000
Connection ~ 4950 1000
Wire Wire Line
	4950 1250 4950 1350
Wire Wire Line
	4950 1650 4950 1750
Wire Wire Line
	4950 1750 4800 1750
Connection ~ 4800 1750
Wire Wire Line
	4950 1000 5500 1000
Connection ~ 4950 1350
Wire Wire Line
	4950 1350 4950 1450
Wire Wire Line
	4950 1750 5200 1750
Wire Wire Line
	5200 1750 5200 1500
Wire Wire Line
	5200 1500 5500 1500
Wire Wire Line
	5500 1500 5500 1100
Connection ~ 4950 1750
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J5
U 1 1 657B7CE5
P 4100 5350
F 0 "J5" V 4104 4862 50  0000 R CNN
F 1 "DispKB" V 4195 4862 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 4100 5350 50  0001 C CNN
F 3 "~" H 4100 5350 50  0001 C CNN
	1    4100 5350
	0    -1   1    0   
$EndComp
Wire Wire Line
	6000 1350 6000 1850
Wire Wire Line
	4950 1350 6000 1350
Wire Wire Line
	4700 2450 5500 2450
Wire Wire Line
	4700 2350 5500 2350
Wire Wire Line
	4700 2250 5500 2250
Text Notes 4450 3500 0    50   ~ 0
D25
Text Notes 5100 3500 0    50   ~ 0
D24
Text Label 4000 5750 1    50   ~ 0
SET
Text Label 4100 5750 1    50   ~ 0
OK
Text Label 4200 5750 1    50   ~ 0
RT
Text Label 4300 5750 1    50   ~ 0
UP
Text Label 4400 5750 1    50   ~ 0
DW
Text Label 4500 5750 1    50   ~ 0
LFT
Text Notes 5350 2550 0    50   ~ 0
A15
$Comp
L Connector_Generic:Conn_02x06_Odd_Even J7
U 1 1 658B5B6E
P 4900 3400
F 0 "J7" H 4950 3950 50  0000 C CNN
F 1 "2x6" H 4950 3850 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x06_P2.54mm_Vertical" H 4900 3400 50  0001 C CNN
F 3 "~" H 4900 3400 50  0001 C CNN
	1    4900 3400
	-1   0    0    -1  
$EndComp
Text Notes 4450 3600 0    50   ~ 0
D26
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J6
U 1 1 658FBE39
P 5800 2250
F 0 "J6" H 5850 2867 50  0000 C CNN
F 1 "2x10" H 5850 2776 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 5800 2250 50  0001 C CNN
F 3 "~" H 5800 2250 50  0001 C CNN
	1    5800 2250
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x01 J3
U 1 1 659076A3
P 5900 4600
F 0 "J3" V 6050 4450 50  0000 C CNN
F 1 "2x1" V 5950 4450 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 5900 4600 50  0001 C CNN
F 3 "~" H 5900 4600 50  0001 C CNN
	1    5900 4600
	0    1    -1   0   
$EndComp
Wire Wire Line
	5500 2550 5350 2550
Wire Wire Line
	6000 2450 6300 2450
Wire Wire Line
	6000 2550 6250 2550
Wire Wire Line
	4700 1350 3300 1350
Connection ~ 4700 1350
Wire Wire Line
	4700 1350 4700 1200
Wire Wire Line
	4800 1300 3250 1300
Connection ~ 4800 1300
Wire Wire Line
	4800 1300 4800 1750
Wire Wire Line
	5500 2650 5450 2650
$Comp
L Connector:Barrel_Jack_Switch_Pin3Ring J10
U 1 1 657D3718
P 3700 6950
F 0 "J10" V 3803 6762 50  0000 R CNN
F 1 "IN" V 3712 6762 50  0000 R CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 3750 6910 50  0001 C CNN
F 3 "~" H 3750 6910 50  0001 C CNN
	1    3700 6950
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J16
U 1 1 6582E322
P 5000 6500
F 0 "J16" H 4800 6450 50  0000 L CNN
F 1 "16" H 5080 6451 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 5000 6500 50  0001 C CNN
F 3 "~" H 5000 6500 50  0001 C CNN
	1    5000 6500
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J15
U 1 1 6583D35D
P 5100 6500
F 0 "J15" H 5000 6450 50  0000 C CNN
F 1 "15" H 5018 6626 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 5100 6500 50  0001 C CNN
F 3 "~" H 5100 6500 50  0001 C CNN
	1    5100 6500
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J14
U 1 1 658443F7
P 5000 6400
F 0 "J14" H 4800 6500 50  0000 L CNN
F 1 "14" H 5080 6351 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 5000 6400 50  0001 C CNN
F 3 "~" H 5000 6400 50  0001 C CNN
	1    5000 6400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J13
U 1 1 6584B48B
P 5100 6400
F 0 "J13" H 5050 6500 50  0000 C CNN
F 1 "13" H 5018 6526 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x01_P2.54mm_Vertical" H 5100 6400 50  0001 C CNN
F 3 "~" H 5100 6400 50  0001 C CNN
	1    5100 6400
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_Switch_Pin3Ring J8
U 1 1 657CA64F
P 5850 6250
F 0 "J8" H 5950 6550 50  0000 R CNN
F 1 "OUT" H 5950 6450 50  0000 R CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 5900 6210 50  0001 C CNN
F 3 "~" H 5900 6210 50  0001 C CNN
	1    5850 6250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4800 6500 4450 6500
Wire Wire Line
	3600 6500 3600 6650
Wire Wire Line
	5300 6400 5350 6400
$Comp
L Connector_Generic:Conn_01x02 J12
U 1 1 658D837E
P 3600 6150
F 0 "J12" H 3500 5950 50  0000 L CNN
F 1 "Batt" H 3500 6250 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x02_P4.6mm_D0.9mm_OD2.1mm" H 3600 6150 50  0001 C CNN
F 3 "~" H 3600 6150 50  0001 C CNN
	1    3600 6150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J17
U 1 1 658DF273
P 3750 6250
F 0 "J17" H 3650 6350 50  0000 L CNN
F 1 "Batt" H 3650 6050 50  0000 L CNN
F 2 "Connector_Wire:SolderWire-0.5sqmm_1x02_P4.6mm_D0.9mm_OD2.1mm" H 3750 6250 50  0001 C CNN
F 3 "~" H 3750 6250 50  0001 C CNN
	1    3750 6250
	-1   0    0    1   
$EndComp
NoConn ~ 6000 1950
NoConn ~ 6000 2050
NoConn ~ 6000 2150
NoConn ~ 6000 2250
NoConn ~ 6000 2350
Text Label 5150 6150 0    50   ~ 0
5V
Text Label 5150 6250 0    50   ~ 0
GND
Wire Wire Line
	4750 6400 4750 6250
Connection ~ 4750 6400
Wire Wire Line
	4750 6400 4800 6400
Text Label 4250 6500 0    50   ~ 0
HVIN
$Comp
L Device:R_Small_US R4
U 1 1 6598326B
P 4450 6750
F 0 "R4" H 4382 6704 50  0000 R CNN
F 1 "2.2M" H 4382 6795 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4450 6750 50  0001 C CNN
F 3 "~" H 4450 6750 50  0001 C CNN
	1    4450 6750
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R5
U 1 1 659844B1
P 4250 6950
F 0 "R5" V 4050 6850 50  0000 L CNN
F 1 "330K" V 4150 6850 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4250 6950 50  0001 C CNN
F 3 "~" H 4250 6950 50  0001 C CNN
	1    4250 6950
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 6650 4450 6500
Connection ~ 4450 6500
Wire Wire Line
	4450 6500 3600 6500
Wire Wire Line
	4450 6850 4450 6950
Text Label 6100 3450 1    50   ~ 0
HVmon
Wire Wire Line
	3700 6400 3700 6600
Wire Wire Line
	3700 6400 4050 6400
Wire Wire Line
	3800 6650 3800 6600
Wire Wire Line
	3800 6600 3700 6600
Connection ~ 3700 6600
Wire Wire Line
	3700 6600 3700 6650
NoConn ~ 5500 2750
NoConn ~ 6000 2750
Wire Wire Line
	6000 2650 6100 2650
Wire Wire Line
	5350 2550 5350 2900
Wire Wire Line
	4700 2550 5250 2550
Wire Wire Line
	3400 3300 3400 5950
Text Notes 3500 3500 1    50   Italic 0
OK
Text Notes 3400 3500 1    50   Italic 0
RT
$Comp
L Connector_Generic:Conn_02x03_Odd_Even J2
U 1 1 5FA666AD
P 5100 4600
F 0 "J2" V 5100 4250 50  0000 L CNN
F 1 "ICSP" V 5200 4200 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 5100 4600 50  0001 C CNN
F 3 "~" H 5100 4600 50  0001 C CNN
	1    5100 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 4900 5300 4900
Wire Wire Line
	5000 4900 4900 4900
Wire Wire Line
	5200 4400 5200 4350
Wire Wire Line
	5200 4350 5400 4350
Wire Wire Line
	5400 4350 5400 6050
Wire Wire Line
	5100 4250 5100 4400
Wire Wire Line
	5100 4900 5100 4950
Text Notes 5400 5200 3    50   Italic 0
SET
Text Notes 6100 2450 0    50   Italic 0
UP
Text Notes 6100 2550 0    50   Italic 0
DW
Text Notes 6200 3100 1    50   Italic 0
LFT
Wire Wire Line
	5200 5050 6000 5050
Wire Wire Line
	5450 2650 5450 2850
Wire Wire Line
	5100 3600 5800 3600
Wire Wire Line
	5600 3200 5100 3200
Wire Wire Line
	4400 3100 4400 3200
Wire Wire Line
	4400 3200 4600 3200
Wire Wire Line
	4400 3100 5500 3100
Wire Wire Line
	5450 2850 6000 2850
Wire Wire Line
	6000 2850 6000 5050
Wire Wire Line
	5250 2950 5900 2950
Wire Wire Line
	5250 2950 5250 2550
Wire Wire Line
	5900 2950 5900 4300
Wire Wire Line
	5100 3300 5400 3300
Wire Wire Line
	5400 3300 5400 3000
Wire Wire Line
	5400 3000 3500 3000
Wire Wire Line
	3500 3000 3500 5850
Wire Wire Line
	3400 3300 4600 3300
Wire Wire Line
	5700 3400 5100 3400
Wire Wire Line
	5400 3500 5100 3500
Wire Wire Line
	4600 3600 4450 3600
Wire Wire Line
	4600 3700 4400 3700
Wire Wire Line
	4400 3700 4400 5150
NoConn ~ 4450 3600
Wire Wire Line
	5100 3700 5100 3800
Wire Wire Line
	5100 3800 4300 3800
Wire Wire Line
	4300 3800 4300 5150
Wire Wire Line
	5100 4250 4000 4250
Wire Wire Line
	4000 4250 4000 5150
Wire Wire Line
	4600 3400 4450 3400
NoConn ~ 4450 3400
Wire Wire Line
	4600 3500 4450 3500
NoConn ~ 4450 3500
Wire Wire Line
	5200 3950 4900 3950
Wire Wire Line
	5300 3950 5300 3900
Wire Wire Line
	5300 3900 3300 3900
Wire Wire Line
	5300 3950 5300 4900
Connection ~ 5300 3950
Wire Wire Line
	4900 4900 4900 3950
Connection ~ 4900 3950
Wire Wire Line
	4900 3950 3250 3950
Wire Wire Line
	4100 5650 4100 5850
Wire Wire Line
	4100 5850 3500 5850
Wire Wire Line
	4200 5650 4200 5950
Wire Wire Line
	4200 5950 3400 5950
Wire Wire Line
	4300 5650 4300 5900
Wire Wire Line
	4400 5650 4400 5850
Wire Wire Line
	4400 5850 6250 5850
Wire Wire Line
	4500 5650 4500 5800
Wire Wire Line
	4500 5800 6200 5800
Wire Wire Line
	4000 6050 4000 5650
Wire Wire Line
	4000 6050 5400 6050
Wire Wire Line
	4500 5050 4500 5150
Wire Wire Line
	4500 5050 5000 5050
Wire Wire Line
	5100 4950 4100 4950
Wire Wire Line
	4100 4950 4100 5150
Wire Wire Line
	5000 4400 4200 4400
Wire Wire Line
	4200 4400 4200 5150
Wire Wire Line
	5350 2900 6200 2900
Wire Wire Line
	6200 5800 6200 2900
Wire Wire Line
	6250 5850 6250 2550
Wire Wire Line
	6300 2450 6300 5900
Wire Wire Line
	4300 5900 6300 5900
Wire Wire Line
	5400 3500 5400 3950
Wire Wire Line
	5500 3100 5500 3950
Wire Wire Line
	5600 3200 5600 3950
Wire Wire Line
	5700 3400 5700 3950
Wire Wire Line
	5800 3600 5800 3950
Wire Wire Line
	5500 4800 5500 5300
Wire Wire Line
	5500 4800 5900 4800
Connection ~ 4750 6250
Wire Wire Line
	5500 6250 5350 6250
Connection ~ 5500 6250
Wire Wire Line
	5500 5500 5500 6250
Wire Wire Line
	4150 6950 4050 6950
Wire Wire Line
	4350 6950 4450 6950
Connection ~ 4450 6950
Wire Wire Line
	5500 6250 5550 6250
Wire Wire Line
	5400 6150 5400 6500
Connection ~ 5400 6150
Wire Wire Line
	5400 6150 5550 6150
Wire Wire Line
	5400 6500 5300 6500
Wire Wire Line
	5350 6400 5350 6250
Connection ~ 5350 6250
Wire Wire Line
	5350 6250 4750 6250
Wire Wire Line
	5500 6250 5500 6350
Wire Wire Line
	5500 6350 5550 6350
Wire Wire Line
	4450 6950 6100 6950
Wire Wire Line
	6100 2650 6100 6950
Wire Wire Line
	4050 6950 4050 6400
Connection ~ 4050 6400
Wire Wire Line
	4050 6400 4750 6400
Wire Wire Line
	3800 5650 3700 5650
Wire Wire Line
	3700 5650 3700 5150
Wire Wire Line
	3700 5150 3800 5150
Wire Wire Line
	3900 5650 3900 5700
Wire Wire Line
	3900 5700 3650 5700
Wire Wire Line
	3650 5700 3650 5100
Wire Wire Line
	3650 5100 3900 5100
Wire Wire Line
	3900 5100 3900 5150
Wire Wire Line
	3950 6250 4750 6250
Wire Wire Line
	3950 6150 5400 6150
Connection ~ 3300 3900
Connection ~ 3250 3950
Wire Wire Line
	3700 5150 3250 5150
Connection ~ 3700 5150
Connection ~ 3250 5150
Wire Wire Line
	3300 3900 3300 5100
Wire Wire Line
	3250 3950 3250 5150
Wire Wire Line
	3650 5100 3300 5100
Connection ~ 3650 5100
Connection ~ 3300 5100
Wire Wire Line
	3300 3900 3300 1350
Wire Wire Line
	3250 1300 3250 3950
Wire Wire Line
	3250 5150 3250 6150
Wire Wire Line
	3300 6250 3400 6250
Wire Wire Line
	3300 5100 3300 6250
Wire Wire Line
	3400 6150 3250 6150
$EndSCHEMATC
