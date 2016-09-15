#pragma once

enum class touch_event {
    began,
    move,
    end,
    cancle
};

const char* to_string(touch_event type);
