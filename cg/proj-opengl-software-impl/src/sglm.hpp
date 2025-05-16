#pragma once

namespace glm
{
	namespace impl {
		template<typename T>
		struct _vec3 {
			// typedef _vec3<T> type;
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
				// todo
				return *this;
			}
			_vec3& operator-=(const _vec3& rhs) {
				// todo
				return *this;
			}

			friend _vec3 operator + (const _vec3& lhs, const _vec3& rhs) {
				return _vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + lhs.z);
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

			T& operator[](int index) { return value[index]; }
			const T& operator[](int index) const { return value[index]; }
		};

		template<typename T>
		struct _mat4 {
			typedef _vec4<T> col_type;

			_mat4(T v) {
				for (int i = 0; i < 4; ++i) {
					value[i] = _vec4<T>(v);
				}
			}

			col_type& operator[](size_t index) { return value[index]; }
			const col_type& operator[](size_t index) const { return value[index]; }

		private:
			col_type value[4];
		};
	}

	typedef impl::_vec3<float> vec3;
	typedef impl::_mat4<float> mat4;

	// https://glm.g-truc.net/0.9.5/api/a00176.html#ga454fdf3163c2779eeeeeb9d75907ce97
	mat4 lookAt(const vec3& eye, const vec3& conter, const vec3& up) {

		return mat4(0); // todo
	}

	float radians(float degrees) {
		return 0; // todo
	}

	vec3 normalize(const vec3& v) {
		return vec3(0); // todo
	}

	vec3 cross(const vec3& a, const vec3& b) {
		// todo
		return vec3();
	}

	mat4 perspective(float fovy, float aspect, float near, float far) {
		return mat4(0); // todo
	}

	mat4 translate(const mat4& m, const vec3& t) {
		return mat4(0); // todo
	}

	mat4 rotate(const mat4& m, float angle, const vec3& axis) {
		return mat4(0); // todo
	}
}
