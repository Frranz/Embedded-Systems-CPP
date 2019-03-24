#include "../include/Printf.h"

char* Printf(char* dst, const void* end, const char* fmt...) {
    //strncpy(dst, fmt, TeststringLength - 1);
    char* startBuff = dst;
    bool lastWasPercent = false;
    va_list args;
    va_start(args, fmt);

    int i;
    int loopCounter;
    std::string s;

    while(dst < end && *fmt != '\0') {
        if(*fmt == '%') {
            if(lastWasPercent) {
                *dst = '%';
                dst++;
                lastWasPercent = false;
            } else {
                lastWasPercent = true;
            }
        } else {
            if(lastWasPercent) {
                switch(*fmt) {
                    case 'd':
                    case 'u':
                        i = va_arg(args, int);
                        s = std::to_string(i);

                        loopCounter = 0;
                        while(s[loopCounter] != '\0' && dst < end && loopCounter < 10) { // biggest 32bit integer has 10 digits
                            *dst = s[loopCounter];
                            dst++;
                            loopCounter++;
                        }
                        break;
                    case 'c':
                        i = va_arg(args, int);
                        *dst = static_cast<char>(i); // char is promoted to int when passed
                        dst++;
                        break;
                    case 's':
                        break;
                    case 'x':
                        break;
                    case 'b':
                        break;
                    default:
                        // return nullptr if unspecified %{character}
                        return nullptr;
                }
                lastWasPercent = false;
            } else {
                *dst = *fmt;
                dst++;
            }
        }

        fmt++;
    }

    return startBuff;
}

int main() {
    printf("turnup hier gehts los\n");
    char printHere[TeststringLength];
    char* formattedString = Printf(printHere, printHere + TeststringLength, "int: %d\nunsginedint: %u\ncharacter: %c\nstring: %s\n", -74, 3, "e", "ripx");
    std::cout << formattedString;

    return 0;
}
