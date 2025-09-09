/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float cx = 0.0;         // center x-coordinate from Pixy
double servoPWM = 127;  // starting servo PWM value
uint8 evasiveMode = 0;  // flag to trigger evasive turns
uint16 frontDistance = 0;    // distance to object behind
uint16 rearDistance = 0;    // distance to object behind

uint8 turn = 0; // variable to decide left or right when obstacle in front but no obstacle detected left or right
uint16 targetSpeed = 3;

// speed control variables
uint16 old_time = 65535;
uint16 new_time;
uint16 elapsed_time;
char strbuf2[32];

double PWM;
volatile double speed;

// speed control PID parameters
double kp = 20; // proportional gain
double ki = .2; // integral gain
double accumulated_error = 0;
double PWM_base = 15;

// speed control
CY_ISR(inter_1) {
    
    // storing the most recently captured time
    new_time = Timer_ReadCapture();
    
    // calculating the elapsed time and accounting for the event of a roll over in the timer
    if(new_time < old_time) elapsed_time = old_time - new_time;
    if(new_time >= old_time) elapsed_time = 65535 - (new_time - old_time);
        
    //clears the timer's status register in preparation for the next interrupt and time capture
    Timer_ReadStatusRegister();
    
    // saving the most recently captured time to be used in calculating elapsed time with the subsequently captured time
    old_time = new_time;
    
    // calculating speed. 1256 is approximation of (2(pi)r) / (5*10^-4), which accounts for scalar of printed time value (10^-4)
    speed = (1256.0 / (double)(elapsed_time));
    
    // summing previous error values for integral term
    accumulated_error += targetSpeed-speed;
    
    // implementing PID control equation to calulate new PWM comparison value
    PWM = PWM_base + kp* (targetSpeed - speed) + ki* accumulated_error;
    
    // creating a string consisiting of the elapsed time, current speed and PWM values
    sprintf(strbuf2, "%u %f %f", elapsed_time, speed, PWM);
    
    // setting limits for the PWM signal
    if(PWM > 100) PWM = 100;
    if(PWM < 20)  PWM = 2;
    
    // outputting the new PWM signal. If the counter in the PWM is less than the comparison value, the signal is high
    PWM_WriteCompare((uint8)PWM);
    
}

// wall detection response
CY_ISR(inter_2) {
    
    // if left distance sensors activated by wall, turn right
    if((P_left_1_Read() == 1) || (P_front_left_Read() == 1) || (P_left_2_Read() == 1))
        servoPWM = 200;
    // if right distance sensors activated by wall, turn left    
    else if((P_right_1_Read() == 1) || (P_front_right_Read() == 1) || (P_right_2_Read() == 1))
        servoPWM = 20; 
    // if only front distance sensor activated by wall, turn left
    else if ((P_front_Read() == 1) && !((P_left_1_Read() == 1) || (P_front_left_Read() == 1) || (P_left_2_Read() == 1)) && !((P_right_1_Read() == 1) || (P_front_right_Read() == 1) || (P_right_2_Read() == 1)))
        servoPWM = 20; 
    
    PWM_1_WriteCompare((uint8)servoPWM); // change servo angle

    // interupt stops fleeMode code so tag parameters included here
    static char rearBuffer[32]; // to hold distance of object in rear camera
    static uint8 readIndex = 0;

    while (UART_1_GetRxBufferSize() > 0) {
        char receivedChar = UART_1_GetChar();

        if (receivedChar == '\r' || receivedChar == '\n') {
            rearBuffer[readIndex] = '\0';
            readIndex = 0;
            
            // extract rc_detected and dist from rearBuffer
            if (strncmp(rearBuffer, "rc_detected:1", 13) == 0) {
                char *distPtr = strstr(rearBuffer, "dist:");  // find "dist:"
                if (distPtr) {
                    rearDistance = atoi(distPtr + 5);  // extract distance value
                    
                    if (rearDistance > 80 && rearDistance < 165) { // RC car is close to being tagged
                        targetSpeed = 4;
                    } else if (rearDistance <= 80) { // RC car is far from being tagged
                        targetSpeed = 3;
                    } else if (rearDistance >= 165){ // RC car has been tagged; stop RC car.
                        STOP_Write(0); // stop car for demo. This line can be removed for continuous back and forth tagging
                        MODE_Write(0); // switch to chase mode
                        UART_1_PutString("Tagged. Now in chase mode. \r\n"); // send tagged to XBee
                    }                    
                }
                else {
                    rearDistance = 0;  // reset distance
                }
            }
            else if (strncmp(rearBuffer, "rc_detected:0", 13) == 0) {
                rearDistance = 0;  // No object detected
            }
        }
        // condition to prevent buffer overflow
        else if (readIndex < sizeof(rearBuffer) - 1) {
            rearBuffer[readIndex++] = receivedChar;
        }
        else {
            readIndex = 0;  // reset buffer on overflow
        }
    }
}

// function to handle front UART input and parse cx value
void chaseMode() {
    static char frontBuffer[32];    // to hold cx value
    static char rearBuffer[32];     // to hold object detection in rear camera
    static char leftBuffer[32];     // to hold object detection in left camera
    static char rightBuffer[32];    // to hold object detection in right camera
    static uint8 frontIndex = 0;
    static uint8 rearIndex = 0;
    static uint8 leftIndex = 0;
    static uint8 rightIndex = 0;
    
    // front camera input
    while (UART_2_GetRxBufferSize() > 0) {
        char receivedChar = UART_2_GetChar();

        if (receivedChar == '\r' || receivedChar == '\n') {
            frontBuffer[frontIndex] = '\0';
            frontIndex = 0;
            
            char *cxPtr = strstr(frontBuffer, "cx:");       // extract cx from frontBuffer
            char *distPtr = strstr(frontBuffer, "dist:");   // extract distance from frontBuffer
            if (cxPtr && distPtr) {
                cx = atof(cxPtr + 3);               // convert cx value to float
                frontDistance = atoi(distPtr + 5);  // convert distance value to integer

                if (frontDistance > 80 && frontDistance < 156) targetSpeed = 4; // RC car is close to tagging autonomous car, speed up
                else if (frontDistance <= 80) targetSpeed = 3; // RC car is far from tagging autonomous car
                else if (frontDistance >= 156) { // RC car tagged autonomous car
                    MODE_Write(1); // switch to flee mode
                    UART_1_PutString("Tagged. Now in Flee mode.\r\n"); // send tag status to XBee
                }
                
                
                if(cx != 0 && frontDistance != 0) {
                    // update servo position by mapping (-1 to 1) to (2 to 250)
                    servoPWM = 124 * cx + 126;
                    
                    // outputting the new PWM signal. If the counter in the PWM is less than the comparison value, the signal is high
                    PWM_1_WriteCompare((uint8)servoPWM);
                }
            }
        }
        // condition to prevent buffer overflow
        else if (frontIndex < sizeof(frontBuffer) - 1) {
            frontBuffer[frontIndex++] = receivedChar;
        }
        else {
            frontIndex = 0;  // reset buffer on overflow
        }
    }
    
    // if autonomous car not visible from the front camera, check if detects by other cameras and turn in that direction
    if (frontDistance == 0){
        // rear camera input
        while (UART_1_GetRxBufferSize() > 0) {
        char receivedChar = UART_1_GetChar();

        if (receivedChar == '\r' || receivedChar == '\n') {
            rearBuffer[rearIndex] = '\0';
            rearIndex = 0;
            
            // if rc_detected turn around
            if (strncmp(rearBuffer, "rc_detected:1", 13) == 0) {
                turn = (rand() % 2);
                if (turn == 0) PWM_1_WriteCompare(20); // turn left 
                else if (turn == 1) PWM_1_WriteCompare(200); // turn right
                CyDelay(2000);
            }
        }
        // condition to prevent buffer overflow
        else if (rearIndex < sizeof(rearBuffer) - 1) {
            rearBuffer[rearIndex++] = receivedChar;
        }
        else {
            rearIndex = 0;  // reset buffer on overflow
        }
    }
        
        // left camera input
        while (UART_3_GetRxBufferSize() > 0) {
            char receivedChar = UART_3_GetChar();

            if (receivedChar == '\r' || receivedChar == '\n') {
                leftBuffer[leftIndex] = '\0';
                leftIndex = 0;
                if (strcmp(leftBuffer, "1") == 0){ // detected, turn left
                    PWM_1_WriteCompare(20);
                }
                else if (strcmp(leftBuffer, "0") == 0) { // not detected, stay straight
                    PWM_1_WriteCompare(127);
                }
            }
            // condition to prevent buffer overflow
            else if (leftIndex < sizeof(leftBuffer) - 1) {
                leftBuffer[leftIndex++] = receivedChar;
            }
            else {
                leftIndex = 0;  // reset buffer on overflow
            }
        }
        
        // right camera input
        while (UART_4_GetRxBufferSize() > 0) {
            char receivedChar = UART_4_GetChar();

            if (receivedChar == '\r' || receivedChar == '\n') {
                rightBuffer[rightIndex] = '\0';
                rightIndex = 0;
                if (strcmp(rightBuffer, "1") == 0){ // detected, turn right
                    PWM_1_WriteCompare(200);
                }
                else if (strcmp(rightBuffer, "0") == 0) { // not detected, stay straight
                    PWM_1_WriteCompare(127);
                }
            }
            // condition to prevent buffer overflow
            else if (rightIndex < sizeof(rightBuffer) - 1) {
                rightBuffer[rightIndex++] = receivedChar;
            }
            else {
                rightIndex = 0;  // reset buffer on overflow
            }
        }
    }
}   

// function to handle rear UART input and parse distance value
void fleeMode() {
    static char rearBuffer[32];     // to hold distance of object in rear camera
    static char leftBuffer[32];     // to hold object detection in left camera
    static char rightBuffer[32];    // to hold object detection in right camera
    static uint8 rearIndex = 0;
    static uint8 leftIndex = 0;    
    static uint8 rightIndex = 0;
    
    // rear camera input
    while (UART_1_GetRxBufferSize() > 0) {
        char receivedChar = UART_1_GetChar();

        if (receivedChar == '\r' || receivedChar == '\n') {
            rearBuffer[rearIndex] = '\0';
            rearIndex = 0;
            
            // extract rc_detected and dist
            if (strncmp(rearBuffer, "rc_detected:1", 13) == 0) {
                char *distPtr = strstr(rearBuffer, "dist:");  // find "dist:"
                if (distPtr) {
                    rearDistance = atoi(distPtr + 5);  // extract distance value
                    
                    if (rearDistance > 80 && rearDistance < 165) { // RC car is close to being tagged
                        evasiveMode = 1;  // Enable evasive mode
                        targetSpeed = 4;
                        UART_1_PutString("Evasive mode activated.\r\n");
                    } else if (rearDistance <= 80) { // RC car is far from being tagged
                        evasiveMode = 0;  // Disable evasive mode
                        targetSpeed = 3;
                        UART_1_PutString("Evasive mode deactivated.\r\n");
                    } else if (rearDistance >= 165){ // RC car has been tagged; stop RC car.
                        STOP_Write(0); // stop car for demo. This line can be removed for continuous back and forth tagging
                        MODE_Write(0); // switch to chase mode
                        UART_1_PutString("Tagged. Now in chase mode.\r\n"); // send tagged to XBee
                    }
                }
                else {
                    // UART_1_PutString("Error: 'dist:' not found in buffer\r\n");
                    rearDistance = 0;  // Reset distance
                    evasiveMode = 0;   // Disable evasive mode
                }
            }
            else if (strncmp(rearBuffer, "rc_detected:0", 13) == 0) {
                rearDistance = 0;  // No object detected
                evasiveMode = 0;   // Disable evasive mode
            }
        }
        // condition to prevent buffer overflow
        else if (rearIndex < sizeof(rearBuffer) - 1) {
            rearBuffer[rearIndex++] = receivedChar;
        }
        else {
            rearIndex = 0;  // reset buffer on overflow
        }
    }
    
    // if autonomous car not detects in rear camera, check other cameras
    if (rearDistance == 0) {
        // left camera input
        while (UART_3_GetRxBufferSize() > 0) {
            char receivedChar = UART_3_GetChar();

            if (receivedChar == '\r' || receivedChar == '\n') {
                leftBuffer[leftIndex] = '\0';
                leftIndex = 0;
                if (strcmp(leftBuffer, "1") == 0){  // detected, turn right
                    PWM_1_WriteCompare(200);
                }
                else if (strcmp(leftBuffer, "0") == 0) { // not detected, stay straight
                    PWM_1_WriteCompare(127);
                }
            }
            // condition to prevent buffer overflow
            else if (leftIndex < sizeof(leftBuffer) - 1) {
                leftBuffer[leftIndex++] = receivedChar;
            }
            else {
                leftIndex = 0;  // reset buffer on overflow
            }
        }
        
        // right camera input
        while (UART_4_GetRxBufferSize() > 0) {
            char receivedChar = UART_4_GetChar();

            if (receivedChar == '\r' || receivedChar == '\n') {
                rightBuffer[rightIndex] = '\0';
                rightIndex = 0;
                if (strcmp(rightBuffer, "1") == 0){ // detected, turn left
                    PWM_1_WriteCompare(20);
                }
                else if (strcmp(rightBuffer, "0") == 0) { // not detected, stay straight
                    PWM_1_WriteCompare(127);
                }
            }
            // condition to prevent buffer overflow
            else if (rightIndex < sizeof(rightBuffer) - 1) {
                rightBuffer[rightIndex++] = receivedChar;
            }
            else {
                rightIndex = 0;  // reset buffer on overflow
            }
        }
    }
}

// function to perform evasive maneuvers
void performEvasiveManeuver() {
    if (evasiveMode) { // evasiveMode is turned on when autonomous car is close to rear
        servoPWM = (rand() % 249) + 2;  // random PWM between 2 and 250
        PWM_1_WriteCompare((uint8)servoPWM);

        // log evasive action
        char log[32];
        sprintf(log, "PWM: %d\r\n", (int)servoPWM);
        UART_1_PutString(log);
        
        // perform turn for 1-3 seconds randomly
        int delayTime = (rand() % 3 + 1) * 1000;  // random delay between 1000ms (1s) and 3000ms (3s)
        CyDelay(delayTime);
        
        // log delay time
        sprintf(log, "Random delay: %d ms\r\n", delayTime);
        UART_1_PutString(log);
        
        evasiveMode = 0;
    }
    else {
        servoPWM = 127;  // random PWM between 2 and 250
        PWM_1_WriteCompare((uint8)servoPWM);    
    }
}

int main(void) {
    CyGlobalIntEnable;  // enable global interrupts

    HE_Interrupt_Start();
    front_interrupt_Start();
    front_right_interrupt_Start();
    front_left_interrupt_Start();
    turn_interrupt_Start();
    Timer_Start();
    PWM_Start();
    
    // inputting the location of the interrupt
    HE_Interrupt_SetVector(inter_1);
    front_interrupt_SetVector(inter_2);
    front_right_interrupt_SetVector(inter_2);
    front_left_interrupt_SetVector(inter_2);
    
    UART_1_Start();     // start UART for rear Arduino
    UART_2_Start();     // start UART for front Arduino
    UART_3_Start();     // start UART for left Arduino
    UART_4_Start();     // start UART for right Arduino
    
    PWM_1_Start();      // start PWM for servo control

    // set initial servo position (centered)
    PWM_1_WriteCompare(127);
    
    srand(time(NULL));  // seed random number generator for evasive maneuvers

    for (;;) {
        if (MODE_Read() == 0) {
            chaseMode();     // process front and side camera feed to chase
        }
        else if (MODE_Read() == 1){
            fleeMode();                 // process rear and side camera feed to flea
            performEvasiveManeuver();   // perform evasive actions if necessary
        }
    }
}