#pragma once
#include <Arduino.h>

#define I2C_DEV_ADDR 0x55 //Einfach nicht ändern
#define MAX_MSG_LEN 32    //Maximal mögliche Package länge
#define PROT_VER 1

#define HSM 1
#define HSS 2
#define MSG 3
#define ERR 4
#define INF 5

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