#pragma once

#include <cmath>
#include <limits>

namespace glm
{
    namespace impl {
        template<typename T>
        struct _vec2 {
            typedef T value_type;

            union {
                struct { T x, y; };
                struct { T r, g; };
                T value[2];
            };

            _vec2(T x, T y) : x(x), y(y) {}
            _vec2(T v) : x(v), y(v) {}
            _vec2() : x(0), y(0) {}

            T& operator[](size_t index) { return value[index]; }
            const T& operator[](size_t index) const { return value[index]; }

            _vec2& operator+=(const _vec2& rhs) {
                x += rhs.x;
                y += rhs.y;
                return *this;
            }
            _vec2& operator-=(const _vec2& rhs) {
                x -= rhs.x;
                y -= rhs.y;
                return *this;
            }

            friend _vec2 operator + (const _vec2& lhs, const _vec2& rhs) {
                return _vec2(lhs.x + rhs.x, lhs.y + rhs.y);
            }

            friend _vec2 operator * (const _vec2& lhs, float s) {
                return _vec2(lhs.x * s, lhs.y * s);
            }
        };

        template<typename T>
        struct _vec3 {
            typedef T value_type;

            union {
                struct { T x, y, z; };
                struct { T r, g, b; };
                T value[3];
            };

            _vec3(T x, T y, T z) : x(x), y(y), z(z) {}
            _vec3(T v) : x(v), y(v), z(v) {}
            _vec3() : x(0), y(0), z(0) {}

            T& operator[](size_t index) { return value[index]; }
            const T& operator[](size_t index) const { return value[index]; }

            _vec3& operator+=(const _vec3& rhs) {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                return *this;
            }
            _vec3& operator-=(const _vec3& rhs) {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                return *this;
            }

            friend _vec3 operator + (const _vec3& lhs, const _vec3& rhs) {
                return _vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
            }

            friend _vec3 operator * (const _vec3& lhs, float s) {
                return _vec3(lhs.x * s, lhs.y * s, lhs.z * s);
            }
        };

        template<typename T>
        struct _vec4 {
            typedef T value_type;

            union {
                struct { T x, y, z, w; };
                struct { T r, g, b, a; };
                T value[4];
            };

            _vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
            _vec4(T v) : x(v), y(v), z(v), w(v) {}
            _vec4() : x(0), y(0), z(0), w(0) {}
            _vec4(_vec3<T> vec3, T w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

            T& operator[](int index) { return value[index]; }
            const T& operator[](int index) const { return value[index]; }

            _vec4& operator+=(const _vec4& rhs) {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                w += rhs.w;
                return *this;
            }
            _vec4& operator-=(const _vec4& rhs) {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                w -= rhs.w;
                return *this;
            }

            friend _vec4 operator + (const _vec4& lhs, const _vec4& rhs) {
                return _vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
            }

            friend _vec4 operator * (const _vec4& lhs, float s) {
                return _vec4(lhs.x * s, lhs.y * s, lhs.z * s, lhs.w * s);
            }
        };

        // column-major order, mat4[i][j] 返回的是第i列第j行的元素
        template<typename T>
        struct _mat4 {
        private:
            typedef _vec4<T> col_type;
            col_type columns[4];

        public:
            _mat4(T v) {
                for (int i = 0; i < 4; ++i) {
                    columns[i] = _vec4<T>(v);
                }
            }

            _mat4(const col_type& col0, const col_type& col1, const col_type& col2, const col_type& col3) {
                columns[0] = col0;
                columns[1] = col1;
                columns[2] = col2;
                columns[3] = col3;
            }

            col_type& operator[](size_t index) { return columns[index]; }
            const col_type& operator[](size_t index) const { return columns[index]; }

            friend _vec4<T> operator * (const _mat4& lhs, const _vec4<T>& rhs) {
                // 这两种方式是相同的
                return lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3] * rhs.w;
                //return _vec4(
                //    lhs[0][0] * rhs.x + lhs[1][0] * rhs.y + lhs[2][0] * rhs.z + lhs[3][0] * rhs.w,
                //    lhs[0][1] * rhs.x + lhs[1][1] * rhs.y + lhs[2][1] * rhs.z + lhs[3][1] * rhs.w,
                //    lhs[0][2] * rhs.x + lhs[1][2] * rhs.y + lhs[2][2] * rhs.z + lhs[3][2] * rhs.w,
                //    lhs[0][3] * rhs.x + lhs[1][3] * rhs.y + lhs[2][3] * rhs.z + lhs[3][3] * rhs.w,
                //);
            }

            friend _mat4 operator * (const _mat4& lhs, const _mat4& rhs) {
                return _mat4(
                    lhs * rhs[0],
                    lhs * rhs[1],
                    lhs * rhs[2],
                    lhs * rhs[3]
                );
            }
        };
    }

    typedef impl::_vec2<float> vec2;
    typedef impl::_vec3<float> vec3;
    typedef impl::_vec4<float> vec4;
    typedef impl::_mat4<float> mat4;

    // degrees to radians
    inline float radians(float degrees) {
        return degrees * (3.14159f / 180.0f);
    }

    // performs a linear interpolation between x and y using a to weight between them
    inline vec4 mix(const vec4& x, const vec4& y, float a) {
#if _DEBUG
        if (a < 0 || a > 1)
            throw "error";
#endif
        return x * (1 - a) + y * a;
    }

    inline vec3 normalize(const vec3& v) {
        float len = v.x * v.x + v.y * v.y + v.z * v.z;
        if (len == 0)
            return vec3(std::numeric_limits<float>::quiet_NaN()); // NaN
        float a = std::sqrtf(1 / len);
        return v * a;
    }

    inline vec3 cross(const vec3& u, const vec3& v) {
        // todo: 推导一遍公式
        return vec3(
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x
        );
    }

    inline mat4 translate(const mat4& m, const vec3& t) {
        // 先通过t构造translate矩阵，然后矩阵相乘，因为translate矩阵的左上角3x3是单位矩阵，所以可以简化计算，只计算第4列
        mat4 ret = mat4(m);
        ret[3] = m[0] * t.x + m[1] * t.y + m[2] * t.z + m[3] * 1;
        return ret;
    }

    inline mat4 rotate(const mat4& m, float angle, const vec3& axis) {

        return mat4(0); // todo
    }

    // Build a look at view matrix.
    // https://glm.g-truc.net/0.9.5/api/a00176.html#ga454fdf3163c2779eeeeeb9d75907ce97
    //	eye		Position of the camera
    //	center	Position where the camera is looking at
    //	up		Normalized up vector, how the camera is oriented. Typically (0, 0, 1)
    inline mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
        return mat4(0); // todo
    }

    inline mat4 perspective(float fovy, float aspect, float near, float far) {
        return mat4(0); // todo
    }
}
