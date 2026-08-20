
typedef enum {
    ALARM_START,
    ALARM_STOP
} alarm_command_t;

typedef struct {
    alarm_command_t command;
    int alarm_id;
} alarm_message_t;
