#ifndef INC_synthetic_h
#define INC_synthetic_h

#include <ross.h>

typedef enum synthetic_evnet_t synthetic_evnet_t;
typedef struct synthetic_state synthetic_state;
typedef struct synthetic_message synthetic_message;

enum synthetic_evnet_t {
    INTERNAL,
    EXTERNAL
};

struct synthetic_state {
    int internal;
    int external;

    tw_stime ts;
};

struct synthetic_message {

    synthetic_evnet_t type;


    tw_stime ts;
};

static int state_size;
static int num_nodes;
static int floating_point_ops_cnt;
static char network[];
static char event_send[];

#endif
