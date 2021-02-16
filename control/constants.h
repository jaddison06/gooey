#pragma once

enum GOOEY_STATUS_CODE
{
    GOOEY_QUIT=0, // GOOEY_QUIT needs to be 0 because it'll be returned by main()
    GOOEY_SUCCESS,
    GOOEY_FAIL
};

enum POSITION_TYPE
{
    ABSOLUTE,
    PERCENTAGE
};