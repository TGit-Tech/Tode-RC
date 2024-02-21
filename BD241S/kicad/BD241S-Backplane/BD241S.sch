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
L Connector_Generic:Conn_02x03_Odd_Even J2
U 1 1 5FA666AD
P 4550 5300
F 0 "J2" V 4600 5200 50  0000 L CNN
F 1 "ICSP" V 4750 5400 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 4550 5300 50  0001 C CNN
F 3 "~" H 4550 5300 50  0001 C CNN
	1    4550 5300
	0    1    1    0   
$EndComp
Text Label 3950 4300 2    50   ~ 0
GND
$Comp
L Connector_Generic:Conn_01x07 J4
U 1 1 5FA69381
P 4650 4500
F 0 "J4" V 4650 4600 50  0000 R CNN
F 1 "E32" V 4750 4300 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 4650 4500 50  0001 C CNN
F 3 "~" H 4650 4500 50  0001 C CNN
	1    4650 4500
	0    -1   1    0   
$EndComp
Text Label 4550 6300 3    50   ~ 0
SDA
Text Label 4650 6450 1    50   ~ 0
RES
Text Label 4750 6450 1    50   ~ 0
RS
Text Label 4850 6450 1    50   ~ 0
CS
Text Label 4950 6450 1    50   ~ 0
BL
Text Label 4450 6450 1    50   ~ 0
SCK
Text Label 4950 4300 1    50   ~ 0
M0
Text Label 4850 4300 1    50   ~ 0
M1
Text Label 4750 4300 1    50   ~ 0
TXD
Text Label 4650 4300 1    50   ~ 0
RXD
Text Label 4550 4300 1    50   ~ 0
AUX
Text Label 3900 4200 2    50   ~ 0
VCC
Wire Wire Line
	4450 5600 4450 5650
Wire Wire Line
	4650 5600 4650 5750
Wire Wire Line
	4950 6250 4950 6450
NoConn ~ 4450 5100
Wire Wire Line
	4550 5600 4550 6450
Wire Wire Line
	4450 6450 4450 5850
Wire Wire Line
	5000 5850 5000 5000
Wire Wire Line
	5000 5000 4550 5000
Wire Wire Line
	4550 5000 4550 5100
Text Notes 3700 3450 0    50   ~ 0
CS
Text Notes 3700 3350 0    50   ~ 0
RES
Text Notes 3550 3250 0    50   ~ 0
D3
Text Notes 4250 3250 0    50   ~ 0
D2
Text Notes 4250 3350 0    50   ~ 0
D4
Text Notes 4250 3450 0    50   ~ 0
D6
Wire Wire Line
	4000 5650 4450 5650
Connection ~ 4000 5650
Wire Wire Line
	4650 5750 4100 5750
Wire Wire Line
	4450 5850 5000 5850
$Comp
L Connector_Generic:Conn_02x07_Odd_Even J7
U 1 1 63D198B1
P 4100 3550
F 0 "J7" H 4150 3800 50  0000 C CNN
F 1 "2x7" V 4150 3350 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x07_P2.54mm_Vertical" H 4100 3550 50  0001 C CNN
F 3 "~" H 4100 3550 50  0001 C CNN
	1    4100 3550
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J5
U 1 1 63E7E48A
P 4550 6650
F 0 "J5" V 4554 6162 50  0000 R CNN
F 1 "DispKB" V 4645 6162 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 4550 6650 50  0001 C CNN
F 3 "~" H 4550 6650 50  0001 C CNN
	1    4550 6650
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 63F1F757
P 4350 4650
F 0 "J6" V 4350 4650 50  0000 R CNN
F 1 "PWR" V 4250 4550 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 4350 4650 50  0001 C CNN
F 3 "~" H 4350 4650 50  0001 C CNN
	1    4350 4650
	0    -1   -1   0   
$EndComp
Connection ~ 4100 5750
Wire Wire Line
	4300 3850 4600 3850
$Comp
L Device:R_Small_US R1
U 1 1 646DA561
P 4450 3950
F 0 "R1" V 4500 3850 50  0000 C CNN
F 1 "10" V 4400 3850 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4450 3950 50  0001 C CNN
F 3 "~" H 4450 3950 50  0001 C CNN
	1    4450 3950
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 646DAEA3
P 4700 3850
F 0 "R2" V 4750 3750 50  0000 C CNN
F 1 "10" V 4650 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4700 3850 50  0001 C CNN
F 3 "~" H 4700 3850 50  0001 C CNN
	1    4700 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 5100 4650 5050
Wire Wire Line
	4200 5050 4650 5050
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 648A4C5E
P 4600 2800
F 0 "J1" H 4550 3100 50  0000 L CNN
F 1 "1x6 MH" V 4700 2500 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4600 2800 50  0001 C CNN
F 3 "~" H 4600 2800 50  0001 C CNN
	1    4600 2800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 648B3CE8
P 4100 2800
F 0 "J3" H 4050 3100 50  0000 L CNN
F 1 "1x6 FH" V 3850 2500 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4100 2800 50  0001 C CNN
F 3 "~" H 4100 2800 50  0001 C CNN
	1    4100 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2700 4400 2700
Connection ~ 3900 2800
Wire Wire Line
	3900 2800 4400 2800
Wire Wire Line
	4400 3100 3900 3100
Wire Wire Line
	4400 3000 3900 3000
Wire Wire Line
	4400 2900 3900 2900
Wire Wire Line
	4400 2600 3900 2600
Text Label 4450 7050 1    50   ~ 0
SET
Text Label 4550 7050 1    50   ~ 0
OK
Text Label 4650 7050 1    50   ~ 0
RT
Text Label 4750 7050 1    50   ~ 0
UP
Text Label 4850 7050 1    50   ~ 0
DW
Text Label 4950 7050 1    50   ~ 0
LFT
Text Label 3700 3850 0    50   ~ 0
RXR
Text Label 4450 3850 0    50   ~ 0
TXR
Text Label 4250 2600 0    50   ~ 0
VIN
Text Label 4250 2900 0    50   ~ 0
3V3
Text Label 4250 3000 0    50   ~ 0
AREF
Text Label 4250 3100 0    50   ~ 0
RX
Text Notes 3550 3350 0    50   ~ 0
D5
Text Notes 3550 3450 0    50   ~ 0
D7
Text Notes 3700 3250 0    50   ~ 0
DW
Text Notes 4250 6450 1    50   ~ 0
GND
Text Notes 4350 6450 1    50   ~ 0
VCC
Text Notes 4250 7050 1    50   ~ 0
GND
Text Notes 4350 7050 1    50   ~ 0
VCC
Text Notes 3700 3750 0    50   ~ 0
SET
Text Notes 4250 3550 0    50   ~ 0
D8
Text Notes 3550 3550 0    50   ~ 0
D9
Text Notes 4250 3650 0    50   ~ 0
D10
Text Notes 3550 3650 0    50   ~ 0
D11
Text Notes 4300 3750 0    50   ~ 0
D12
Text Notes 3550 3750 0    50   ~ 0
D13
Text Notes 4300 3850 0    50   ~ 0
D14
Text Notes 3550 3850 0    50   ~ 0
D15
Text Notes 3700 3550 0    50   ~ 0
M1
Text Notes 4450 3550 0    50   ~ 0
M0
Text Notes 4450 3450 0    50   ~ 0
RS
Text Notes 4450 3350 0    50   ~ 0
BL
Text Notes 4450 3250 0    50   ~ 0
LFT
Text Notes 3700 3650 0    50   ~ 0
RT
Text Notes 4450 3750 0    50   ~ 0
OK
Text Notes 4450 3650 0    50   ~ 0
UP
Wire Wire Line
	3800 3250 3000 3250
Wire Wire Line
	4300 3250 5500 3250
Wire Wire Line
	5500 3250 5500 7100
Connection ~ 3900 2700
Wire Wire Line
	3800 3350 3100 3350
Wire Wire Line
	3200 3450 3800 3450
Wire Wire Line
	3100 3350 3100 6050
Wire Wire Line
	4300 3350 5400 3350
Wire Wire Line
	5400 3350 5400 6250
Wire Wire Line
	4950 6250 5400 6250
Wire Wire Line
	4750 6450 4750 6150
Wire Wire Line
	4750 6150 5300 6150
Wire Wire Line
	5300 6150 5300 3450
Wire Wire Line
	5300 3450 4300 3450
Wire Wire Line
	3800 3550 3500 3550
Wire Wire Line
	3500 3550 3500 4050
Wire Wire Line
	3500 4050 4850 4050
Wire Wire Line
	3300 3650 3800 3650
Wire Wire Line
	3800 3750 3400 3750
Wire Wire Line
	4250 7050 4000 7050
Wire Wire Line
	4250 6950 4250 7050
Wire Wire Line
	4100 7150 4350 7150
Wire Wire Line
	4350 6950 4350 7150
Wire Wire Line
	4450 7250 3400 7250
Wire Wire Line
	4450 6950 4450 7250
Wire Wire Line
	3400 3750 3400 7250
Wire Wire Line
	4650 7350 3300 7350
Wire Wire Line
	3300 3650 3300 7350
Wire Wire Line
	4650 6950 4650 7350
Wire Wire Line
	4850 7450 3000 7450
Wire Wire Line
	4850 6950 4850 7450
Wire Wire Line
	3000 3250 3000 7450
Wire Wire Line
	4300 3750 5100 3750
Wire Wire Line
	4100 5750 4100 6150
Wire Wire Line
	4850 5950 3200 5950
Wire Wire Line
	4850 5950 4850 6450
Wire Wire Line
	3200 5950 3200 3450
Wire Wire Line
	4650 6050 3100 6050
Wire Wire Line
	4650 6050 4650 6450
Wire Wire Line
	4350 6150 4100 6150
Wire Wire Line
	4350 6150 4350 6450
Connection ~ 4100 6150
Wire Wire Line
	4100 6150 4100 7150
Wire Wire Line
	4000 5650 4000 6250
Wire Wire Line
	4250 6450 4250 6250
Wire Wire Line
	4250 6250 4000 6250
Connection ~ 4000 6250
Wire Wire Line
	4000 6250 4000 7050
Wire Wire Line
	4950 6950 4950 7100
Wire Wire Line
	4750 6950 4750 7200
Wire Wire Line
	5200 3650 5200 7200
Wire Wire Line
	4950 7100 5500 7100
Wire Wire Line
	4550 7300 5100 7300
Wire Wire Line
	4550 6950 4550 7300
Wire Wire Line
	4750 7200 5200 7200
Wire Wire Line
	5100 7300 5100 3750
Wire Wire Line
	3600 3950 3600 3850
Wire Wire Line
	3600 3850 3800 3850
Wire Wire Line
	3600 3950 4350 3950
Wire Wire Line
	4550 3950 4650 3950
Wire Wire Line
	4800 3850 4850 3850
Wire Wire Line
	4850 3850 4850 3950
Wire Wire Line
	4850 3950 4750 3950
Wire Wire Line
	4650 3950 4650 4300
Wire Wire Line
	4750 3950 4750 4300
Wire Wire Line
	4850 4050 4850 4300
Wire Wire Line
	4300 3550 4950 3550
Wire Wire Line
	4300 3650 5200 3650
Wire Wire Line
	4950 3550 4950 4300
Wire Wire Line
	4350 4300 4350 4850
Wire Wire Line
	4450 4300 4450 4850
Wire Wire Line
	4350 4850 4350 4900
Wire Wire Line
	4350 4900 4000 4900
Connection ~ 4350 4850
Wire Wire Line
	4000 4900 4000 5650
Wire Wire Line
	4450 4850 4450 4950
Wire Wire Line
	4450 4950 4100 4950
Connection ~ 4450 4850
Wire Wire Line
	4100 4950 4100 5750
Wire Wire Line
	4450 4300 4450 4200
Wire Wire Line
	4450 4200 2900 4200
Connection ~ 4450 4300
Connection ~ 4350 4300
Wire Wire Line
	4550 4100 4200 4100
Wire Wire Line
	4550 4100 4550 4300
Wire Wire Line
	4200 4100 4200 5050
Wire Wire Line
	2900 2800 2900 4200
Wire Wire Line
	2900 2800 3900 2800
Wire Wire Line
	2800 2700 2800 4300
Wire Wire Line
	2800 2700 3900 2700
Wire Wire Line
	2800 4300 4350 4300
$EndSCHEMATC
