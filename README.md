# TestExec

A single-header library to create simple unit tests as individual executables. Made to be used with the Meson build system's unit testing system.

## Features

- Easy to integrate into your project
- No external dependencies past the C Standard Library
- Just basic assertion and logging functionality

## Installing

Simply clone this repository using the following command in your terminal:

```bash
git clone https://github.com/edwindick/testexec
```

Then copy the [testexec.h](testexec.h) file from your newly created directory to whatever project you intend to use TestExec with.

## Sample Code

```c
// file - tests/fizzbuzz.c

// Hypothetical project containing the function "fizzbuzz()," which takes in a
// single 8-bit integer and outputs the string "Fizz" if the number is divisible 
// by three, "Buzz" if divisible by five, or "FizzBuzz" if divisible by both
// numbers. Otherwise it will simply write the value of the integer passed as
// a string to the output array.
#include <project/fizzbuzz.h>

#include <string.h>     // For comparing strings.

#include "testexec.h"   // Or wherever testexec.h is placed relative to your
                        // source file

// Note that the `test` macro simply expands to `int main`. This means that
// you could add argument parameters to this function, if you so wish to do so
// for whatever reason... 
test(void) {
    // For writing simple logging messages.
    TEST_MESSAGE("Begin test: %s", "fizzbuzz.");

    char out[FIZZBUZZ_MAX_RETURN_SIZE] = { 0 };
    fizzbuzz(1, out);

    // `TEST_ASSERT()` works much like how the C Standard Library's `assert()`
    // function does. If the condition supplied isn't true, then an message is
    // reported to stdout and the application quits prematurely. Unlike C's
    // `assert()` function, these are still checked on release builds.
    TEST_ASSERT(strcmp(out, "1") == 0); // True! The program continues.

    fizzbuzz(2, out);

    // Works exactly like the previous assert function described, but allows
    // the program to continue execution even if the supplied condition is
    // false.
    TEST_ASSERT_PASS(strcmp(out, "Fizz") == 0)  // False! The program continues
                                                // anyways.

    // Counterpart would be `TEST_RETURN_FAILED`.
    return TEST_RETURN_PASSED;
}

// There are also two macros left unmentioned above that you may use:
// `TEST_PASSED()` and `TEST_FAILED(),` both of which exit the test prematurely
// with their respective error codes. Both allow you to write an optional 
// message to stdout before exiting. For example, `TEST_PASSED("Wow!")` and
// `TEST_PASSED()` will both compile without warning.
```

## Key Macros

- `TEST_ASSERT(condition)` 
  - Stops the test if the condition is false.
- `TEST_ASSERT_PASS(condition)`
  - Logs failures but continues the test.
- `TEST_MESSAGE("Message")`
  - Logs a custom message to stdout.
- `TEST_PASSED("Message")` / `TEST_FAILED("Message")` / `TEST_SKIPPED("Message")`
    - Exits the test prematurely, with or without a specified message.

## License

This project is distributed under the MIT License. See the [LICENSE](LICENSE) file for details.
