#pragma once

#include <algorithm>
#include <vector>

class myShiftNeighbor {
  
 public:

  myShiftNeighbor() = default;
  myShiftNeighbor(int from, int to, int size) : myShiftNeighbor{} {
    set(from, to, size);
  }

  /**
   * Apply move on a solution regarding a key
   * @param _sol the solution to move
   */
  void move(std::vector<int>& _sol) {
    if (static_cast<int>(key) >= 0) {
      unsigned int tmp;
      size = _sol.size();
      translate(key + 1);
      // keep the first component to change
      tmp = _sol[first];
      // shift
      if (first < second) {
        for (unsigned int i = first; i < second - 1; i++)
          _sol[i] = _sol[i + 1];
        // shift the first component
        _sol[second - 1] = tmp;
      } else { /* first > second*/
        for (unsigned int i = first; i > second; i--)
          _sol[i] = _sol[i - 1];
        // shift the first component
        _sol[second] = tmp;
      }
    } else {
      auto begin = _sol.begin();
      if (first == second) {
        return;
      } else if (first < second) {
        std::rotate(begin + first, begin + first + 1, begin + second + 1);
      } else {
        std::rotate(begin + second, begin + first, begin + first + 1);
      }
      _sol.invalidate();
    }
  }

  void set(unsigned first, unsigned second, unsigned size) {
    this->first = first;
    this->second = second;
    this->size = size;
    this->key = static_cast<unsigned>(-1);
  }

  auto firstSecond(EOT& _sol) -> std::pair<unsigned, unsigned> {
    return firstSecond(_sol.size());
  }

  auto firstSecond(int solSize) -> std::pair<unsigned, unsigned> {
    if (static_cast<int>(key) >= 0) {
      size = solSize;
      translate(key + 1);
      if (first < second)
        second--;
    }
    return {first, second};
  }

  /**
   * fix two indexes regarding a key
   * @param _key the key allowing to compute the two indexes for the shift
   */
  void translate(unsigned int _key) {
    int step;
    int val = _key;
    int tmpSize = size * (size - 1) / 2;
    // moves from left to right
    if (val <= tmpSize) {
      step = size - 1;
      first = 0;
      while ((val - step) > 0) {
        val = val - step;
        step--;
        first++;
      }
      second = first + val + 1;
    }
    // moves from right to left (equivalent moves are avoided)
    else { /* val > tmpSize */
      val = val - tmpSize;
      step = size - 2;
      second = 0;
      while ((val - step) > 0) {
        val = val - step;
        step--;
        second++;
      }
      first = second + val + 1;
    }
  }

 private:
  unsigned int first;
  unsigned int second;
  unsigned int size;
};
