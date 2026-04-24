#pragma once
#include <Arduino.h>

#define I2C_DEV_ADDR 0x55 //Einfach nicht ändern
#define MAX_MSG_LEN 32    //Maximal mögliche Package länge
#define PROT_VER 2

#define HSM 1       //HandShake Master
#define HSS 2       //HandShake Slave
#define SPH 3       //Set Pin High
#define SPL 4       //Set Pin Low
//To be added to

struct Package {
    uint8_t index;               // Typ des Package
    char message[MAX_MSG_LEN];   // Inhalt des Package
    uint8_t length;              // Length of message
};

// Helper: fill a package safely
inline Package makePackage(uint8_t idx, const char* msg) {
    Package p;
    p.index = idx;
    strncpy(p.message, msg, MAX_MSG_LEN);
    p.message[MAX_MSG_LEN - 1] = '\0';
    p.length = strlen(p.message);
    return p;
}