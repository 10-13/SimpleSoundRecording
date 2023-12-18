#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>

template <typename T>
using SPtr = std::shared_ptr<T>;

using Str = std::string;

template <typename T>
using Vec = std::vector<T>;

using IStr = std::istream;

using OStr = std::ostream;