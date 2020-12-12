/*! \mainpage Introduction
 * 
 * \section Overview Conceptual Overview
 * Just as variables point to values in memory every device will have a collection of specific-use class variable types
 * that contain various counts of link-list dynamic Name->Value pairs.
 *  
 *  - Names
 *    - MenuName      for use when no value is needed (like a menu line allows linking to other 'SubList' of items)
 *  
 *  - Values ( Also contains MenuName )
 *    - MVDigitSet    for number values with ability to set them by Menu
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
 *        2. RETURN Changes the CurrList if KEYRIGHT or KEYLEFT or GOTO_SUBLIST
 *    - MenuList::Navigate
 *        1. SENDS the KEY to CurrItem if one is selected.
 *        2. RETURN Changes CurrItem if KEYUP or KEYDOWN
 *    - MenuItem::Navigate (Handled by Each Item as coded)
 *        1. Depending on *Selected* Item-Component
 *        2. KEYRIGHT changes 'Selected' Item-Component
 *        3. KEYOKAY checks for *SubList* and returns GOTO_SUBLIST
 *        4. If nothing handles the key within Item it gets returned back to List
 *        
 * \section DEVICE New Devices        
 *    - Each Device-Type is a class
 *        - *Local* Devices has device *Settings* (i.e. IO-Pin)
 *        - *All* Devices have *Control* (i.e. On/Off and Read-Only)
 *    - Each Device-Type has a \ref KEY
 *    - Tode.cpp AddDevice
 *    - Main.cpp FinalKey
 *    
 * 
 * \section IO-HDW New IO-HDW
 *    - Create (2) 32-bit longs and (1) byte and assign bit-wise usable Pins
 *        1. Used in DevLib.cpp PinSelect::ChangeSetTo
 *        2. Name Pin Usage in PinSelect::PinSelect Constructor
 */
