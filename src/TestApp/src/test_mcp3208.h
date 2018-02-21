#ifndef TEST_MCP3208_H
#define TEST_MCP3208_H
#include "mcp3208.h"

class TestMCP3208
{
public:
    TestMCP3208() = delete;

    static void testAdc();

private:
    static void readCallback(const TaskId id, const uint32_t* data, const Byte length);

    static MCP3208 adc;

};

#endif // TEST_MCP3208_H
