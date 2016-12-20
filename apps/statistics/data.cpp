#include "data.h"
#include <float.h>

namespace Statistics {

Data::Data() :
  m_numberOfPairs(0),
  m_binWidth(1.0f)
{
}

int Data::numberOfPairs() const {
  return m_numberOfPairs;
}

float Data::binWidth() {
  return m_binWidth;
}

float Data::valueAtIndex(int index) {
  return m_values[index];
}

int Data::sizeAtIndex(int index) {
  return m_sizes[index];
}

void Data::setValueAtIndex(float value, int index) {
  m_values[index] = value;
  if (index >= m_numberOfPairs) {
    m_sizes[index] = 1;
    m_numberOfPairs++;
  }
}

void Data::setSizeAtIndex(int size, int index) {
  m_sizes[index] = size;
  if (index >= m_numberOfPairs) {
    m_values[index] = 0.0f;
    m_numberOfPairs++;
  }
}

void Data::deletePairAtIndex(int index) {
  m_numberOfPairs--;
  for (int k = index; k < m_numberOfPairs; k++) {
    m_values[k] = m_values[k+1];
    m_sizes[k] = m_sizes[k+1];
  }
  m_values[m_numberOfPairs] = 0.0f;
  m_sizes[m_numberOfPairs] = 1;
}

int Data::sizeAtValue(float value) {
  float min = xMin();
  float bin = binWidth();
  int binNumber = (value - min)/bin;
  float lowerBound = min + binNumber*bin;
  float upperBound = min + (binNumber+1)*bin;
  int result = 0;
  for (int k = 0; k < m_numberOfPairs; k++) {
    if (m_values[k] < upperBound && lowerBound <= m_values[k]) {
      result += m_sizes[k];
    }
  }
  return result;
}

float Data::xMin() {
  float valueMin = FLT_MAX;
  for (int k = 0; k < m_numberOfPairs; k++) {
    if (m_values[k] < valueMin) {
      valueMin = m_values[k];
    }
  }
  return valueMin;
}

float Data::xMax() {
  float valueMax = -FLT_MAX;
  for (int k = 0; k < m_numberOfPairs; k++) {
    if (m_values[k] > valueMax) {
      valueMax = m_values[k];
    }
  }
  float valueMin = xMin();
  if (valueMax - valueMin >  k_maxRangeValue) {
    valueMax = valueMin + 10.0f;
  }
  return valueMax + binWidth();
}

float Data::yMin() {
  return 0.0f;
}

float Data::yMax() {
  float sizeMax = -FLT_MAX;
  for (float x = xMin(); x < xMax(); x += binWidth()) {
    float size = sizeAtValue(x);
    if (size > sizeMax) {
      sizeMax = size;
    }
  }
  return sizeMax;
}

float Data::xGridUnit() {
  return computeGridUnit(Axis::X);
}

}