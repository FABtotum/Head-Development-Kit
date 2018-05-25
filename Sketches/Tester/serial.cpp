#include "Tester.ino"
#include "tester.h"
#include "serial.h"

bool serial_enabled = false;

static SoftwareSerial * soft_serial;
static char serial_buffer[255] = "";

void serial_start(byte rx, byte tx);
void serial_begin(unsigned long baudrate);
bool serial_available(void);
char* serial_readline (byte nchars);
void serial_end (void);

inline void serial_write (char c_out) { soft_serial->write(c_out); }


bool serial_parse (const char* command, long pin, const char* arg)
{
    switch (command[1])
    {
        case 's': {
            byte rx = pin & 0xff;
            byte tx = strtol(arg, 0, 10);
            serial_start(rx, tx);
            return true;
        }
        case 'r': {
            if (serial_available()) {
                char* str = serial_readline(pin);
                byte  base = strtol(arg, NULL, 10);
                wait(serial_lock);
                if (base) {
                    for (int i=0; i < strlen(str); i++) {
                        Serial.println(str[i], base);
                    }
                } else {
                    Serial.println(str);
                }
                release(serial_lock);
            }
            return true;
        }
        case 'w': {
            byte count = pin;
            for (unsigned short i = 0; i < count; i++) {
                char c_out = arg[i];
                if (c_out != 0) {
                    serial_write(c_out);
                } else {
                    serial_write('\n');
                    break;
                }
            }
            return true;
        }
        case 'b': {
            unsigned long baud = pin;
            serial_begin(baud);
            return true;
        }
    }

    errmsg = ERR_UNRECOGNIZED_COMMAND;
    return false;
}

void serial_start(byte rx, byte tx)
{
    if (serial_enabled) serial_end();

    if (soft_serial) delete soft_serial;

    soft_serial = new SoftwareSerial(rx, tx);
    if (INFO) {
        wait(serial_lock);
        Serial.print("// Start Serial rx=");
        Serial.print(rx);
        Serial.print(" tx=");
        Serial.println(tx);
        release(serial_lock);
    }
}

void serial_begin(unsigned long baudrate)
{
    if (!soft_serial) return;

    soft_serial->begin(baudrate);
    if (INFO) {
        wait(serial_lock);
        Serial.print("// Begin Serial @ ");
        Serial.println(baudrate);
        release(serial_lock);
    }
    serial_enabled = true;
}

bool serial_available ()
{
    if (serial_enabled) {
        return soft_serial->available();
    } else {
        return false;
    }
}

void serial_end ()
{
    serial_enabled = false;
}

char* serial_readline (byte nchars = 255)
{
    if (nchars == 0) nchars = 255;

    for (byte serial_p = 0; serial_p < nchars && soft_serial->available(); serial_p++)
    {
        char c_in = soft_serial->read();
        if (c_in == '\n') {
            serial_buffer[serial_p] = 0;
            break;
        } else {
            serial_buffer[serial_p] = c_in;
        }
    }
    return serial_buffer;
}
