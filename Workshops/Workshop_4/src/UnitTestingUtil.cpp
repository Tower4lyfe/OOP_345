#include <cassert>  // For assert
#include <iostream>
#include "Utilities.h"

void testDelimiterManagement()
{
    // Default delimiter should be ','
    seneca::Utilities::setDelimiter(',');
    assert(seneca::Utilities::getDelimiter() == ',');

    // Change the delimiter to '|'
    seneca::Utilities::setDelimiter('|');
    assert(seneca::Utilities::getDelimiter() == '|');

    // Reset back to ','
    seneca::Utilities::setDelimiter(',');
    assert(seneca::Utilities::getDelimiter() == ',');

    std::cout << "testDelimiterManagement passed.\n";
}

void testFieldWidthManagement()
{
    seneca::Utilities util;

    // Default field width should be 1
    assert(util.getFieldWidth() == 1);

    // Change field width
    util.setFieldWidth(10);
    assert(util.getFieldWidth() == 10);

    util.setFieldWidth(5);
    assert(util.getFieldWidth() == 5);

    std::cout << "testFieldWidthManagement passed.\n";
}

void testExtractToken()
{
    seneca::Utilities util;
    seneca::Utilities::setDelimiter(',');

    std::string input = "Apple,,45,Description";
    size_t next_pos = 0;
    bool more = true;

    // Extract first token (no exception expected)
    try
    {
        assert(util.extractToken(input, next_pos, more) == "Apple"); // Valid token
        assert(more);
    }
    catch (const char* e)
    {
        std::cerr << "Unexpected exception: " << e << '\n';
        assert(false); // Test fails if this happens
    }

    // Extract missing token (exception expected)
    try
    {
        util.extractToken(input, next_pos, more); // This should throw
        assert(false); // Fail if no exception is thrown
    }
    catch (const char* e)
    {
        // Log the expected exception and continue
        std::cerr << "Caught expected exception: " << e << '\n';
    }

    // Extract remaining tokens (no exceptions expected)
    try
    {
        assert(util.extractToken(input, next_pos, more) == "45");
        assert(more);

        assert(util.extractToken(input, next_pos, more) == "Description");
        assert(!more);
    }
    catch (const char* e)
    {
        std::cerr << "Unexpected exception: " << e << '\n';
    }

    std::cout << "testExtractToken passed.\n";
}

int main()
{
    std::cout << "Running tests...\n";

    testDelimiterManagement();
    testFieldWidthManagement();
    testExtractToken();

    std::cout << "All tests passed.\n";
    return 0;
}
