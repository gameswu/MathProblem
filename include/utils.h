// utils.h
#pragma once

#include <vector>

/* 寻找`num`的所有`digit`位数的因数
 * @param num: 待寻找因数的数
 * @param digit: 因数的位数
 */
std::vector<int> find_factors(int num, int digit);

/* 随机寻找`num`的一个`digit`位数的因数
 * @param num: 待寻找因数的数
 * @param digit: 因数的位数
 *
 * Note: 如果找不到则返回-1
 */
int find_a_factor(int num, int digit);