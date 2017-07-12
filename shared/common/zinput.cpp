#include "zinput.h"

const char* to_string(touch_event type)
{
    switch (type)
    {
        case touch_event::began: return "began";
        case touch_event::move:  return "move";
        case touch_event::end:   return "end";
        case touch_event::cancle: return "cancle";
    }
    return "invalid";
}
