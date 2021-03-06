/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2021 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MICRO_TEST_PLUS_MICRO_TEST_PLUS_H_
#define MICRO_TEST_PLUS_MICRO_TEST_PLUS_H_

// ----------------------------------------------------------------------------

#ifdef __cplusplus

namespace os
{
  namespace mtp // `micro-test-plus` is shortened to `mtp`.
  {
    class test
    {
    public:
      test ();

      test (int argc, char* argv[]);

      test (const test&) = delete;
      test (test&&) = delete;
      test&
      operator= (const test&)
          = delete;
      test&
      operator= (test&&)
          = delete;

      ~test () = default;

      void
      init (int argc, char* argv[]);

      void
      start_suite (const char* name);

      void
      run_test_case (void (*f) (test&), const char* name);

      void
      pass (const char* message, const char* file = nullptr, int line = 0);

      void
      fail (const char* message, const char* file = nullptr, int line = 0);

      void
      expect_true (bool condition, const char* message,
                   const char* file = nullptr, int line = 0);

      void
      expect_eq (int actual, int expected, const char* message,
                 const char* file = nullptr, int line = 0);

      void
      expect_eq (long actual, long expected, const char* message,
                 const char* file = nullptr, int line = 0);

      void
      expect_eq (const char* actual, const char* expected, const char* message,
                 const char* file = nullptr, int line = 0);

      int
      result (void);

      inline int
      passed (void)
      {
        return passed_;
      };

      inline int
      failed (void)
      {
        return failed_;
      };

      inline int
      test_cases (void)
      {
        return test_cases_;
      };

    protected:
      void
      print_where_ (const char* format, const char* file, int line);

    protected:
      int argc;
      char** argv;

      const char* name_;

      unsigned int passed_;
      unsigned int failed_;
      unsigned int test_cases_;
    };
  } // namespace mtp
} // namespace os

// ----------------------------------------------------------------------------

// Macros are only a convenience to pass the file name and line number,
// otherwise the direct methods can be used as well.
#define MTP_EXPECT_EQ(t, actual, expected, message) \
  t.expect_eq (actual, expected, message, __FILE__, __LINE__)
#define MTP_EXPECT_TRUE(t, condition, message) \
  t.expect_true (condition, message, __FILE__, __LINE__)

#define MTP_PASS(t, message) t.pass (message, __FILE__, __LINE__)
#define MTP_FAIL(t, message) t.fail (message, __FILE__, __LINE__)

// ----------------------------------------------------------------------------

#endif // __cplusplus

// ----------------------------------------------------------------------------

#endif // MICRO_TEST_PLUS_MICRO_TEST_PLUS_H_

// ----------------------------------------------------------------------------
