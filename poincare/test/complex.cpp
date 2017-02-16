#include <quiz.h>
#include <poincare.h>
#include <string.h>
#include <ion.h>
#include <assert.h>

using namespace Poincare;

QUIZ_CASE(poincare_complex_to_text) {
  char buffer[14];
  Complex::convertFloatToText(123.456f,buffer, 14, 7);
  char result1[20] = {'1','.','2','3','4','5','6',Ion::Charset::Exponent,'2',0};
  assert(strcmp(buffer, result1) == 0);
  Complex::convertFloatToText(1.234567891011f,buffer, 14, 7);
  char result2[20] = {'1','.','2','3','4','5','6','8',Ion::Charset::Exponent,'0',0};
  assert(strcmp(buffer, result2) == 0);
  Complex::convertFloatToText(2.0f, buffer, 14, 7);
  char result3[20] = {'2','.','0',Ion::Charset::Exponent,'0',0};
  assert(strcmp(buffer, result3) == 0);
  Complex::convertFloatToText(123456789.0f, buffer, 14, 7);
  char result4[20] = {'1','.','2','3','4','5','6','8',Ion::Charset::Exponent,'8',0};
  assert(strcmp(buffer, result4) == 0);
  Complex::convertFloatToText(0.00000123456789f, buffer, 14, 7);
  char result5[20] = {'1','.','2','3','4','5','6','8',Ion::Charset::Exponent,'-','6',0};
  assert(strcmp(buffer, result5) == 0);
  Complex::convertFloatToText(0.99f, buffer, 14, 7);
  char result6[20] = {'9','.','9',Ion::Charset::Exponent,'-','1',0};
  assert(strcmp(buffer, result6) == 0);
  Complex::convertFloatToText(-123.456789f, buffer, 14, 7);
  char result7[20] = {'-','1','.','2','3','4','5','6','8',Ion::Charset::Exponent,'2',0};
  assert(strcmp(buffer, result7) == 0);
  Complex::convertFloatToText(-0.000123456789f, buffer, 14, 7);
  char result8[20] = {'-','1','.','2','3','4','5','6','8',Ion::Charset::Exponent,'-','4',0};
  assert(strcmp(buffer, result8) == 0);
  Complex::convertFloatToText(0.0f, buffer, 14, 7);
  char result9[20] = {'0','.','0',Ion::Charset::Exponent,'0',0};
  assert(strcmp(buffer, result9) == 0);
  Complex::convertFloatToText(10000000000000000000000000000.0f, buffer, 14, 7);
  char result10[20] = {'1','.','0',Ion::Charset::Exponent,'2','8',0};
  assert(strcmp(buffer, result10) == 0);
  Complex::convertFloatToText(10000000000000000000000000000.0f, buffer, 14, 7, Expression::DisplayMode::Auto);
  assert(strcmp(buffer, result10) == 0);
  Complex::convertFloatToText(1000000.0f, buffer, 14, 7, Expression::DisplayMode::Auto);
  assert(strcmp(buffer, "1000000") == 0);
  Complex::convertFloatToText(10000000.0f, buffer, 14, 7, Expression::DisplayMode::Auto);
  char result11[20] = {'1','.','0',Ion::Charset::Exponent,'7',0};
  assert(strcmp(buffer, result11) == 0);
  Complex::convertFloatToText(0.000001f, buffer, 14, 7, Expression::DisplayMode::Auto);
  assert(strcmp(buffer, "0.000001") == 0);
  Complex::convertFloatToText(0.0000001f, buffer, 14, 7, Expression::DisplayMode::Auto);
  char result12[20] = {'1','.','0',Ion::Charset::Exponent,'-','7',0};
  assert(strcmp(buffer, result12) == 0);
  char buffer2[6];
  Complex::convertFloatToText(123.421f, buffer2, 6, 4, Expression::DisplayMode::Auto);
  assert(strcmp(buffer2, "123.4") == 0);
  char buffer3[6];
  Complex::convertFloatToText(123.421f, buffer3, 6, 5, Expression::DisplayMode::Auto);
  char result13[20] = {'1','.','2',Ion::Charset::Exponent,'2',0};
  assert(strcmp(buffer3, result13) == 0);

  Complex(1, 2).writeTextInBuffer(buffer, 14);
  char text1[14] = {'1','+', '2', '*', Ion::Charset::SmallIota, 0};
  assert(strcmp(buffer, text1) == 0);
  Complex(-1.3, 2.444).writeTextInBuffer(buffer, 14);
  char text2[14] = {'-','1','.','3','+', '2','.','4','4','4', '*', Ion::Charset::SmallIota, 0};
  assert(strcmp(buffer, text2) == 0);
  Complex(-1.3, -2.444).writeTextInBuffer(buffer, 14);
  char text3[14] = {'-','1','.','3','-', '2','.','4','4','4', '*', Ion::Charset::SmallIota, 0};
  assert(strcmp(buffer, text3) == 0);
}

QUIZ_CASE(poincare_complex_approximate) {
  GlobalContext globalContext;
  Expression * a = new Complex(123.456f);
  assert(a->approximate(globalContext) == 123.456f);
  delete a;
}

QUIZ_CASE(poincare_complex_evaluate) {
  GlobalContext globalContext;
  Expression * a = new Complex(123.456f);
  Expression * e = a->evaluate(globalContext);
  assert(e->approximate(globalContext) == 123.456f);
  delete a;
  delete e;
}

QUIZ_CASE(poincare_complex_constructor) {
  Complex * a = new Complex(2.0f, 3.0f, false);
  assert(a->a() == 2.0f && a->b() == 3.0f);
  assert(a->r() == 3.60555124f && a->th() == 0.982793748f);
  delete a;

  a = new Complex(3.60555124f, 0.982793748f, true);
  assert(a->a() == 2.0f && a->b() == 3.0f);
  delete a;
}