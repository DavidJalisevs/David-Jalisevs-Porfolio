#include "MyVector2.h"

/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
/// 
/// potential note for rotation 
/// Rotation of 90 degrees - translate points to (-b, a)
/// Rotation of 180 degrees - translate points to(-a, -b)
/// Rotation of 270 degrees - translate points to(b, -a)
/// Rotation of 360 degrees - translate points to(a, b) which is just staying at the initial shape
/// 
/// 
/// --------------------------------------------------------------------------------------------------
/// --------------------------------------------------------------------------------------------------
/// 
/// 
///        
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x ) + (t_vector.y * t_vector.y);
	const float length = sqrt(sumOfSquares);
	return length;
}                  

float vectorLengthSquared(sf::Vector2f t_vector)
{
	float vectorSquared = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	return vectorSquared;
}

float vectorCorssProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float crossProduct = (t_vectorA.x * t_VectorB.y) - (t_vectorA.y * t_VectorB.x);
	return crossProduct;
}

float vectorDotProduct(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB)
{
	float dotProduct = (t_vectorA.x * t_VectorB.x) + (t_vectorA.y * t_VectorB.y);
	return dotProduct;
}

float vectorAngleBetween(sf::Vector2f t_vectorA, sf::Vector2f t_VectorB) 
{
	float dotProduct = (t_vectorA.x * t_VectorB.x) + (t_vectorA.y * t_VectorB.y);
	float magnitudeA = sqrtf((t_vectorA.x * t_vectorA.x) + (t_vectorA.y * t_vectorA.y));
	float magnitudeB = sqrtf((t_VectorB.x * t_VectorB.x) + (t_VectorB.y * t_VectorB.y));
	float angleBetween =  acosf ((dotProduct )/ (magnitudeA * magnitudeB));
	angleBetween = angleBetween * (180 /PI );
	return angleBetween;
}

sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	float cosAngle = cos(t_angleRadians);
	float sinAngle = sin(t_angleRadians);
	float xAngle = (t_vector.x * cosAngle) - (t_vector.y * sinAngle);
	float yAngle = (t_vector.x * sinAngle) + (t_vector.y * cosAngle);
	sf::Vector2f rotation{ xAngle, yAngle };
	return rotation;
}


sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float projecScale = vectorDotProduct(t_vector, t_onto) / vectorLengthSquared(t_onto);
	sf::Vector2f vecProjec = t_onto * projecScale;
	return vecProjec;
}

sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f vecRejec = t_vector - vectorProjection(t_vector, t_onto);
	return vecRejec;
}

float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float scalarProjec = vectorDotProduct(t_vector, t_onto) / vectorLength(t_onto);
	return scalarProjec;
}

sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	sf::Vector2f vecUnit{ 0.0f, 0.0f };
	float lenght = vectorLength(t_vector);
	
	if (lenght != 0.0f)
	{
		vecUnit = sf::Vector2f{ t_vector.x / lenght, t_vector.y / lenght };
	}

	return vecUnit;
}
