#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <porto/utility.h>

namespace porto
{
	class Vec3
	{
	public:
		union
		{
			double e[3];
			struct
			{
				double r;
				double g;
				double b;
			};
			struct
			{
				double x;
				double y;
				double z;
			};
		};

		// initializer
		explicit Vec3() : x{0}, y{0}, z{0} {}
		explicit Vec3(double e0, double e1, double e2) : x{e0}, y{e1}, z{e2} {}
		Vec3(const Vec3 &v) : x{v.x}, y{v.y}, z{v.z} {}

		inline const Vec3& operator+() const { return *this; }
		inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
		inline double operator[](int i) const { return e[i]; }
		inline double& operator[](int i) { return e[i]; }

		inline Vec3& operator+=(const Vec3 &v2);
		inline Vec3& operator-=(const Vec3 &v2);
		inline Vec3& operator*=(const Vec3 &v2);
		inline Vec3& operator/=(const Vec3 &v2);
		inline Vec3& operator*=(const double t);
		inline Vec3& operator/=(const double t);

		inline double length() const { return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); }
		inline double squared_length() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
		inline void normalize();
	};

	inline std::istream& operator>>(std::istream &is, Vec3 &t) {
		is >> t.e[0] >> t.e[1] >> t.e[2];
		return is;
	}

	inline std::ostream& operator<<(std::ostream &os, const Vec3 &t) {
		os << t.e[0] << " " << t.e[1] << " " << t.e[2];
		return os;
	}

	inline void Vec3::normalize() {
		double k = 1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
		e[0] *= k; e[1] *= k; e[2] *= k;
	}

	inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
	}

	inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
	}

	inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
	}

	inline Vec3 operator*(double t, const Vec3 &v) {
		return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	inline Vec3 operator*(const Vec3 &v, double t) {
		return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
	}

	inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
	}

	inline Vec3 operator/(Vec3 v, double t) {
		return Vec3(v.e[0]/t, v.e[1]/t, v.e[2]/t);
	}

	inline double dot(const Vec3 &v1, const Vec3 &v2) {
		return v1.e[0]*v2.e[0]
			 + v1.e[1]*v2.e[1]
			 + v1.e[2]*v2.e[2];
	}

	inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
		return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
					v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
					v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
	}

	inline Vec3& Vec3::operator+=(const Vec3 &v) {
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator-=(const Vec3& v) {
		e[0] -= v.e[0];
		e[1] -= v.e[1];
		e[2] -= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator*=(const Vec3 &v) {
		e[0] *= v.e[0];
		e[1] *= v.e[1];
		e[2] *= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline Vec3& Vec3::operator/=(const Vec3 &v) {
		e[0] /= v.e[0];
		e[1] /= v.e[1];
		e[2] /= v.e[2];
		return *this;
	}

	inline Vec3& Vec3::operator/=(const double t) {
		double k = 1.0/t;
		e[0] *= k;
		e[1] *= k;
		e[2] *= k;
		return *this;
	}

	inline Vec3 normalize(Vec3 v) {
		return v / v.length();
	}

	Vec3 random_unit_vector();
}