#include "law.h"
#include <cmath>
#include <float.h>

namespace Probability {

Law::Law() :
 Shared::CurveViewRange()
{
}

float Law::xGridUnit() {
  return computeGridUnit(Axis::X, xMin(), xMax());
}

double Law::cumulativeDistributiveFunctionAtAbscissa(double x) const {
  if (!isContinuous()) {
    int end = std::round(x);
    double result = 0.0;
    for (int k = 0; k <=end; k++) {
      result += evaluateAtDiscreteAbscissa(k);
      /* Avoid too long loop */
      if (result > k_maxProbability || k > k_maxNumberOfOperations) {
        break;
      }
    }
    return result;
  }
  return 0.0;
}

double Law::rightIntegralFromAbscissa(double x) const {
  if (isContinuous()) {
    return 1.0 - cumulativeDistributiveFunctionAtAbscissa(x);
  }
  return 1.0 - cumulativeDistributiveFunctionAtAbscissa(x-1.0);
}

double Law::finiteIntegralBetweenAbscissas(double a, double b) const {
  if (b < a) {
    return 0.0;
  }
  if (isContinuous()) {
    return cumulativeDistributiveFunctionAtAbscissa(b) - cumulativeDistributiveFunctionAtAbscissa(a);
  }
  int start = std::round(a);
  int end = std::round(b);
  double result = 0.0;
  for (int k = start; k <=end; k++) {
    result += evaluateAtDiscreteAbscissa(k);
    /* Avoid too long loop */
    if (result > k_maxProbability || k-start > k_maxNumberOfOperations) {
      break;
    }
  }
  return result;
}

double Law::cumulativeDistributiveInverseForProbability(double * probability) {
  if (*probability >= 1.0) {
    return INFINITY;
  }
  if (isContinuous()) {
    return 0.0;
  }
  if (*probability <= 0.0) {
    return 0.0;
  }
  double p = 0.0;
  int k = 0;
  while (p < *probability && k < k_maxNumberOfOperations) {
    p += evaluateAtDiscreteAbscissa(k++);
  }
  if (k == k_maxNumberOfOperations) {
    *probability = 1.0;
    return INFINITY;
  }
  *probability = p;
  if (std::isnan(*probability)) {
    return NAN;
  }
  return k-1.0f;
}

double Law::rightIntegralInverseForProbability(double * probability) {
  if (isContinuous()) {
    double f = 1.0 - *probability;
    return cumulativeDistributiveInverseForProbability(&f);
  }
  if (*probability >= 1.0) {
    return 0.0;
  }
  if (*probability <= 0.0) {
    return INFINITY;
  }
  double p = 0.0;
  int k = 0;
  while (p < 1.0 - *probability && k < k_maxNumberOfOperations) {
    p += evaluateAtDiscreteAbscissa(k++);
  }
  if (k == k_maxNumberOfOperations) {
    *probability = 1.0;
    return INFINITY;
  }
  *probability = 1.0 - (p - evaluateAtDiscreteAbscissa(k-1));
  if (std::isnan(*probability)) {
    return NAN;
  }
  return k-1.0;
}

double Law::evaluateAtDiscreteAbscissa(int k) const {
  return 0.0;
}

}
