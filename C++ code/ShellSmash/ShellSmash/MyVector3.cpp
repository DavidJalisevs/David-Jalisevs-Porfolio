  /// <summary>
/// Vector 3 class
/// David Jalisevs
/// </summary>
#include "MyVector3.h"
#include <string.h>
const float  PI = 3.14159265358979f;

/// <summary>
/// Default constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0f },
	y{ 0.0f },
	z{ 0.0f }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

MyVector3::MyVector3(float t_x, float t_y, float t_z) 
{
	x = t_x;
	y = t_y;
	z = t_z;
}

/// <summary>
/// print out the value of the vector
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and separated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;	
}

/// <summary>
/// create a vector 3 from an sf::vector3f
/// </summary>
/// <param name="t_sfVector">input vector</param>
MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = t_sfVector.x;
	y = t_sfVector.y;
	z = t_sfVector.z;
}

MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = 0;
}

/// <summary>
/// return a sf::vector2f using x and y as constructor values
/// </summary>
/// <returns></returns>
MyVector3::operator sf::Vector2f()
{
	return sf::Vector2f{ x, y };
}


MyVector3 MyVector3::operator+(const MyVector3 t_right) const
{
	return MyVector3(x+t_right.x, y+t_right.y, z+t_right.z);
}

MyVector3 MyVector3::operator-(const MyVector3 t_right) const
{
	return MyVector3(x - t_right.x, y - t_right.y, z - t_right.z);
}

MyVector3 MyVector3::operator*(const float t_scalar) const
{
	return MyVector3(x * t_scalar, y * t_scalar, z * t_scalar);
}

MyVector3 MyVector3::operator/(const float t_divisor) const
{
	return MyVector3(x / t_divisor, y / t_divisor, z / t_divisor);
}

MyVector3 MyVector3::operator+=(const MyVector3 t_right)
{
	return MyVector3(x += t_right.x, y += t_right.y, z += t_right.z);
}

MyVector3 MyVector3::operator-=(const MyVector3 t_right)
{
	return MyVector3(x -= t_right.x, y -= t_right.y, z -= t_right.z);
}

bool MyVector3::operator==(const MyVector3 t_right) const
{
	if(x==t_right.x && y == t_right.y && z == t_right.z)
	return false;
}

bool MyVector3::operator!=(const MyVector3 t_right) const
{
	if(x != t_right.x && y != t_right.y && z != t_right.z)
	return false;
}

MyVector3 MyVector3::operator-() const
{
	return MyVector3(x*-1, y*-1, z*-1);
}

void MyVector3::reverseX()
{
	x = -x;
}

void MyVector3::reverseY()
{
	y = -y;
}


float MyVector3::length() const
{
	const float result = std::sqrtf(x * x + y* y + z * z);
	return result;
}

float MyVector3::lengthSquared() const
{
	const float result = std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2);
	return result;
}

float MyVector3::dot(const MyVector3 t_other) const
{
	const float result = x * t_other.x + y * t_other.y + z * t_other.z;
	return result;
}

MyVector3 MyVector3::crossProduct(const MyVector3 t_other) const
{
	const float newX = y * t_other.z - z * t_other.y;
	const float newY = z * t_other.x - x * t_other.z;
	const float newZ = x * t_other.y - y * t_other.x;
	return MyVector3{ newX, newY, newZ };
}

float MyVector3::angleBetween(const MyVector3 t_other) const
{
	// formula
	// angle = arccos (a dot b / |a|*|b|)
	float top = dot(t_other);
	float under = length() * t_other.length();
	float angleRadians;
	if (under != 0) // never divide by zero
	{
		float answer = top / under;
		if (answer > 1.0f)
		{
			answer = 1.0f;
		}
		if (answer < -1.0f)
		{
			answer = -1.0f;
		}
		angleRadians = std::acos(answer);
		const float angleDegrees = angleRadians * 180.0f / PI;
		return angleDegrees;
	}
	return 0.0f; // angle with null vector is zero according to Pete ?
}


MyVector3 MyVector3::unit() const
{
	MyVector3 unitVector{};
	float vectorLenght = length();
	if (vectorLenght != 0.0)
	{
		const float unitX = x / vectorLenght;
		const float unitY = y / vectorLenght;
		const float unitZ = z / vectorLenght;
		unitVector = { unitX, unitY, unitZ };
	}
	return unitVector;
}

void MyVector3::normalise()
{
	const float orignalLenght = length();
	if (orignalLenght != 0.0f)
	{
		x /= orignalLenght;
		y /= orignalLenght;
		z /= orignalLenght;
	}
}

MyVector3 MyVector3::projection(const MyVector3 t_other) const
{
	float lenghtSq = t_other.lengthSquared();
	float dotProduct = dot(t_other);
	float scale{ 1.0f }; // default for null vector involvement
	if (lenghtSq != 0.0f)
	{
		scale = dotProduct / lenghtSq;
	}
	return t_other * scale;
}

MyVector3 MyVector3::rejection(const MyVector3 t_onto) const
{
	MyVector3 thisVector{ x,y,z };
	MyVector3 projection = thisVector.projection(t_onto);
	return (thisVector - projection);
	/*
	clever way perhaps not the best
	return this¬>operator¬(projection(t_onto));
	*/
}

MyVector3::operator sf::Vector3i()
{
	return sf::Vector3i{ static_cast<int>(std::round(x)),static_cast<int>
	(std::round(y)), static_cast<int>(std::round(z)) };
}

MyVector3::operator sf::Vector3f()
{
	return sf::Vector3f{ x,y,z };
}


MyVector3::operator sf::Vector2i()
{
	return sf::Vector2i{ static_cast<int>(std::round(x)),static_cast<int>
	(std::round(y)) };
}

MyVector3::operator sf::Vector2u()
{
	float newx{ x };
	float newy{ y };
	if (newx < 0.0f)
	{
		newx = -newx;
	}
	if (newy < 0.0f)
	{
		newy = -newy;
	}
	return sf::Vector2u{ static_cast<unsigned>(std::round
	(newx)),static_cast<unsigned>(std::round(newy)) };
}
