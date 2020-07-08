#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <cinttypes>
#include <cstdint>
#include <ctime>
#include <cstdlib>

namespace celadon {

    using FLOAT = float;
    const FLOAT K_PI = 3.14159265358979323846;
    const FLOAT K_INV_PI = 1.f / K_PI;
    const FLOAT K_EPSILON = 1e-5f;

    template <typename Type>
    class Point2 {
    public:
        Type x, y;

        Point2()
            : x(0.f), y(0.f) {}

        Point2(const Point2& source)
            : x(source.x), y(source.y) {}

        Point2(const Type x, const Type y)
            : x(x), y(y) {}

        Point2(const Type value)
            : x(value), y(value) {}

        Point2<Type>& operator=(const Point2& other) {
            x = other.x;
            y = other.y;
            return *this;
        }

        Point2<Type>& operator+(const Point2& other) {
            return Point2<Type>(x + other.x, y + other.y);
        }
    };

    template <typename Type>
    std::ostream& operator<<(std::ostream& os, const Point2<Type>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    template <typename Type>
    class Point3 {
    public:
        Type x, y, z;

        Point3()
            : x(0.f), y(0.f), z(0.f) {}

        Point3(const Point3& source)
            : x(source.x), y(source.y), z(source.z) {}

        Point3(const Type x, const Type y, const Type z)
            : x(x), y(y), z(z) {}

        Point3(const Type value)
            : x(value), y(value), z(value) {}

        Point3<Type>& operator=(const Point3& other) {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Point3<Type> operator+(const Point3& other) {
            return Point3<Type>(x + other.x, y + other.y, z + other.z);
        }
    };

    template <typename Type>
    std::ostream& operator<<(std::ostream& os, const Point3<Type>& p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }

    template <typename Type>
    class Vector3 {
    private:
    public:
        Type x, y, z;

        Vector3()
            : x(0.0), y(0.0), z(0.0) {}

        Vector3(const Vector3& source)
            : x(source.x), y(source.y), z(source.z) {}

        Vector3(const FLOAT x, const FLOAT y, const FLOAT z)
            : x(x), y(y), z(z) {}

        Vector3(const FLOAT x)
            : x(x), y(x), z(x) {}

        ~Vector3() {}

        Type length() const {
            return sqrt(x * x + y * y + z * z);
        }

        Vector3 normalize() const {
            auto norm = length();
            return Vector3(x / norm, y / norm, z / norm);
        }

        Type dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 cross(const Vector3& other) {
            return Vector3(y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x);
        }

        Vector3 operator-() const {
            return Vector3(-x, -y, -z);
        }

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(const Vector3& other) const {
            return Vector3(x * other.x, y * other.y, z * other.z);
        }

        Vector3 operator/(const Vector3& other) const {
            return Vector3(x / other.x, y / other.y, z / other.z);
        }

        Vector3 operator+(const Type k) const {
            return Vector3(x + k, y + k, z + k);
        }

        Vector3 operator-(const Type k) const {
            return Vector3(x - k, y - k, z - k);
        }

        Vector3 operator*(const Type k) const {
            return Vector3(x * k, y * k, z * k);
        }

        Vector3 operator/(const Type k) const {
            return Vector3(x / k, y / k, z / k);
        }

        friend Vector3 operator*(const Type k, const Vector3& v) {
            return Vector3(k * v.x, k * v.y, k * v.z);
        }

        Vector3 operator+=(const Vector3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3 operator-=(const Vector3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3 operator*=(const Vector3& other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vector3 operator/=(const Vector3& other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Vector3 operator+=(const Type k) {
            x += k;
            y += k;
            z += k;
            return *this;
        }

        Vector3 operator-=(const Type k) {
            x -= k;
            y -= k;
            z -= k;
            return *this;
        }

        Vector3 operator*=(const Type k) {
            x *= k;
            y *= k;
            z *= k;
            return *this;
        }

        Vector3 operator/=(const Type k) {
            x /= k;
            y /= k;
            z /= k;
            return *this;
        }

        bool operator==(const Vector3& other) {
            if (x != other.x) return false;
            if (y != other.y) return false;
            if (z != other.z) return false;
            return true;
        }

        bool operator==(const Type x) {
            if (x != x) return false;
            if (y != x) return false;
            if (z != x) return false;
            return true;
        }

        bool operator!=(const Vector3& other) {
            if (x != other.x) return true;
            if (y != other.y) return true;
            if (z != other.z) return true;
            return false;
        }

        bool operator!=(const Type x) {
            if (x != x) return true;
            if (y != x) return true;
            if (z != x) return true;
            return false;
        }

        friend std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
            stream << '(' << v.x << ',' << v.y << ',' << v.z << ')';
            return stream;
        }

        void clamp() {
            if (x > 1.0) x = 1.0;
            else if (x < 0.0) x = 0.0;

            if (y > 1.0) y = 1.0;
            else if (y < 0.0) y = 0.0;

            if (z > 1.0) z = 1.0;
            else if (z < 0.0) z = 0.0;
        }
    };

    class RNG {
    protected:
        const FLOAT RAND_MAx;
        uint64_t state_;

    public:
        RNG()
            : RAND_MAx(1.0 / UINT64_MAX) {
            set_seed((uint64_t)time(NULL));
        };

        virtual ~RNG() = default;

        void set_seed(uint64_t seed) {
            state_ = seed;
        }

        // This RNG uses xorshift* algorithm basically to generate pseudo-random numbers.
        // Code below is from https://en.wikipedia.org/wiki/Xorshift
        virtual FLOAT rand() {
            uint64_t x = state_;
            x ^= x >> 12;
            x ^= x << 25;
            x ^= x >> 27;
            state_ = x;
            return (FLOAT)((x * 0x2545F4914F6CDD1D) * RAND_MAx);
        }
    };

    using Color3f = Vector3<FLOAT>;
    using Vec3f = Vector3<FLOAT>;
    using Normal3f = Vector3<FLOAT>;
    using Point2f = Point2<FLOAT>;
    using Point2i = Point2<int32_t>;
    using Point3f = Point3<FLOAT>;

    template <typename Type>
    Point3<Type> operator+(const Point3<Type>& a, const Vector3<Type>& v) {
        return Point3<Type>(a.x + v.x, a.y + v.y, a.z + v.z);
    }
    
    template <typename Type>
    Point3<Type> operator-(const Point3<Type>& a, const Vector3<Type>& v) {
        return Point3<Type>(a.x - v.x, a.y - v.y, a.z - v.z);
    }

    template <typename Type>
    Vector3<Type> operator-(const Point3<Type>& a, const Point3<Type>& b) {
        return Vector3<Type>(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    inline static Point2f sample_disk_uniform(const Point2f& u) {
        FLOAT r = std::sqrt(u.x);
        FLOAT theta = 2 * K_PI * u.y;
        return Point2f(r * std::cos(theta), r * std::sin(theta));
    }

    inline static Vec3f sample_hemisphere_cosine(const Point2f& u) {
        Point2f d = sample_disk_uniform(u);
        FLOAT z = std::sqrt(std::max((FLOAT)0, 1 - d.x * d.x - d.y * d.y));
        return Vec3f(d.x, d.y, z);
    }

    static void RGB_clamp(Color3f& color) {
        if (color.x > 1.0) color.x = 1.0;
        else if (color.x < 0.0) color.x = 0.0;

        if (color.y > 1.0) color.y = 1.0;
        else if (color.y < 0.0) color.y = 0.0;

        if (color.z > 1.0) color.z = 1.0;
        else if (color.z < 0.0) color.z = 0.0;
    }
    
    static Color3f background_color(const Vec3f& dir) {
        auto normalized = dir.normalize();
        FLOAT t = 0.5 * (normalized.y + 1.0);
        return (1.0-t)*Color3f(1, 1, 1) + t*Color3f(0.5, 0.7, 1.0);
    }

    template <typename Type>
    Type sign(const Type& value) {
        return value < 0 ? -1 : 1;
    }

};

#endif // MATH_HPP
