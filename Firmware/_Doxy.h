/*! \mainpage Main Page
 * 
 * \section Files Files & Abreviations
 *  - Firmware DateCode [YYMD]
 *    - YY = Last two digits of the Year
 *    - M = (1-9 is Jan-Sept),(A-C is Oct-Dec)
 *    - D = (1-9 is 1-9),(A-V is 10-31)
 *  - ABC   = Analog Button Capture
 *  - DB    = Debug directives
 *  - Disp  = Instantiates the Display Object to use
 *  - E32   = Control of the EBYTE E32-Radio Module
 *  - RFC   = RF Control Protocol Implementation ( RxPacket, TxPacket, RadioI )
 *  - Menu  = Menu Base Classes ( MenuItem, MenuList, Navigator )
 *  - miLib = [m]enu-[i]tem(s) for Basic Name-to-Value Operations
 *  - miHdw = [m]enu-[i]tem(s) for Hardware Selection
 *  - miDev = [m]enu-[i]tem(s) for IO Devices
 *  - miRF  = [m]enu-[i]tem(s) for a Radio Module
 *  
 *
 * \section Overview Conceptual Overview
 * Just as variables point to values in memory every device will have a collection of specific-use class variable types
 * that contain various counts of link-list dynamic Name->Value pairs.
 *  
 *  - Names
 *    - MenuName      for use when no value is needed (like a menu line allows linking to other 'SubList' of items)
 *  
 *  - Values ( Also contains MenuName )
 *    - MenuValueDigSet    for number values with ability to set them by Menu
 *    - MVOptions     for selectable values showing text options
 *    
 *  - Common Accronyms in Code
 *      - AEB         [A]llocation-Size of [E]EPROM in [B]ytes
 *      - EEA         [EE]PROM [A]ddress
 *      - EMC         [E]EPROM [M]emory [C]onstants
 *      - EMO         [E]EPROM [M]emory Address [O]ffsets
 *
 * \section Display Display-Type Encapsulation
 *    - Encapsulated and changeable in Display.h 
 *        - Creates static object *oDisplay* that is assigned to *Display* in every Constructor
 *        - DSPCLASS Constant is used to change Display Libraries
 *        - Implements various display call changes by Constants
 *        
 * \section Navigation User-Navigation
 *    The round-robin \ref KEY processing is done by passing the KEY down to the deepest Link-List pointer level
 *    available at which point the KEY is either USED, REPLACED or RETURNED back up the Link-List tree.  The display
 *    is also controlled by Navigate() calls.
 *    
 *    - Navigator::Navigate
 *        1. SENDS the KEY to CurrList
 *        2. RETURN Changes the CurrList if NAVKEYRIGHT or NAVKEYLEFT or NAVGOTOSUBLIST
 *    - MenuList::Navigate
 *        1. SENDS the KEY to CurrItem if one is selected.
 *        2. RETURN Changes CurrItem if NAVKEYUP or NAVKEYDOWN
 *    - MenuItem::Navigate (Handled by Each Item as coded)
 *        1. Depending on *Selected* Item-Component
 *        2. NAVKEYRIGHT changes 'Selected' Item-Component
 *        3. NAVKEYOKAY checks for *SubList* and returns NAVGOTOSUBLIST
 *        4. If nothing handles the key within Item it gets returned back to List
 *        
 * \section DEVICE New Devices        
 *    - Each Device-Type is a class
 *        - *Local* Devices has device *Settings* (i.e. IO-Pin)
 *        - *All* Devices have *Control* (i.e. On/Off and Read-Only)
 *    - Each Device-Type has a \ref KEY
 *    - Tode.cpp AddDevice
 *    - Sys.cpp FinalKey
 *    
 * \section EEPROM EEPROM Allocation Map
 *    1.  ThisTode Configuration will always start from the beginning of EEPROM Space
 *    2.  Remote Tode's
 *    3.  System Settings
 *        - Including ThisTode's Device Settings (not control)
 *    
 * \section IO-HDW New IO-HDW
 *    - Create (2) 32-bit longs and (1) byte and assign bit-wise usable Pins
 *        1. Used in DevLib.cpp PinSelect::ChangeSetTo
 *        2. Name Pin Usage in PinSelect::PinSelect Constructor
 */
