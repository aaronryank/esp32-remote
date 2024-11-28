#ifndef _DEVICES_H
#define _DEVICES_H

// declarations

#define RESPONSE_ACK "ack"
#define RESPONSE_ERROR "err"
#define RESPONSE_INCOMING "more:"

typedef const uint8_t addr_t[6];

addr_t broadcast_addr, \
       master_addr,    \
       fd_addr,        \
       hp_addr,        \
       gp_addr,        \
       car_addr        \

typedef enum {
    MASTER,
    FDOOR,
    HOUSE,
    GARAGE,
    VEHICLE
};

typedef struct _slave_t {
    addr_t address;
    const char *activator;
} slave_t;

// declarations

const slave_t devices[5];

#endif // _DEVICES_H
