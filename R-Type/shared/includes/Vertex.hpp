#pragma once

#include <iostream>

extern const int blockSize = 64;

template<typename T = int>
struct Vertex
{
    Vertex(T initX = 0, T initY = 0) : x(initX), y(initY) {

    }

    template<typename F>
    Vertex(const Vertex<F>& other) : x(other.x), y(other.y) {

    }

    template<typename F>
    const Vertex operator+(const Vertex<F>& other) const {
        Vertex<T> res(x + other.x, y + other.y);
        return res;
    }

    template<typename F>
    const Vertex operator-(const Vertex<F>& other) const {
        Vertex<T> res(x - other.x, y - other.y);
        return res;
    }

    template<typename F>
    const Vertex operator*(const Vertex<F>& other) const {
        Vertex<T> res(x * other.x, y * other.y);
        return res;
    }

    template<typename F>
    const Vertex operator/(const Vertex<F>& other) const {
        Vertex<T> res(x / other.x, y / other.y);
        return res;
    }

    template<typename F>
    const Vertex& operator=(const Vertex<F>& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return (*this);
    }

    template<typename F>
    const Vertex& operator+=(const Vertex<F>& other) {
        if (this != &other) {
            x += other.x;
            y += other.y;
        }
        return (*this);
    }

    template<typename F>
    const Vertex& operator-=(const Vertex<F>& other) {
        if (this != &other) {
            x -= other.x;
            y -= other.y;
        }
        return (*this);
    }

    template<typename F>
    const Vertex& operator*=(const F& other) {
        if (this != &other) {
            x *= other;
            y *= other;
        }
        return (*this);
    }

    template<typename F>
    const Vertex& operator/=(const F& other) {
        if (this != &other) {
            x /= other;
            y /= other;
        }
        return (*this);
    }

    template<typename F>
    bool operator==(const F& other) {
        return ((x == other.x) && (y == other.y));
    }

    // Convert the pixel coordinate into blocks
    Vertex<T> toBlock() {
        return (Vertex<int>(static_cast<int>(x) / blockSize, static_cast<int>(y) / blockSize));
    }

    // Get block position in pixels
    Vertex<T>  toPix() {
        return (Vertex<int>(static_cast<int>(x) * blockSize, static_cast<int>(y) * blockSize));
    }

    T       x;
    T       y;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vertex<T>& vertex) {
    os << "(" << vertex.x << ", " << vertex.y << ")";
    return (os);
}
s