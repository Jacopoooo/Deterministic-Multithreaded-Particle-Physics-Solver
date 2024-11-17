#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "SFML/Graphics.hpp"

#define LOG(x) std::cout << x << std::endl;
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

template <typename VecType>
static VecType magnitude(const sf::Vector2<VecType> v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

template <typename VecType>
static VecType dotProduct(const sf::Vector2<VecType> v1, const sf::Vector2<VecType> v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename VecType>
static VecType distance(const sf::Vector2<VecType> v1, const sf::Vector2<VecType> v2) {
	return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

static float getRandomFloat(const float min, const float max) {
    static std::random_device rd;  // seme per il generatore
    static std::mt19937 gen(rd()); // generatore Mersenne Twister
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}