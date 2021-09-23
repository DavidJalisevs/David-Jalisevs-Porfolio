//Name : Dawid Jerdonek

#include "MyVector2.h"
#include "Game.h"
/// <summary>
/// get length of vector using sqrt of the sum of the squares
/// </summary>
/// <param name="t_vector">input vector</param>
/// <returns>length</returns>
float vectorLength(sf::Vector2f t_vector)
{
	float sumOfSquares = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	const float length = std::sqrt(sumOfSquares);
	return length;
}

float vectorLengthSquared(sf::Vector2f t_vector)
{
	float lengthSquared = (t_vector.x * t_vector.x) + (t_vector.y * t_vector.y);
	return lengthSquared;
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
	float magnitudeOfA = sqrtf(t_vectorA.x * t_vectorA.x) + (t_vectorA.y * t_vectorA.y);
	float magnitudeOfB = sqrtf(t_VectorB.x * t_VectorB.x) + (t_VectorB.y * t_VectorB.y);
	float angleInBetween = acosf(dotProduct / (magnitudeOfA * magnitudeOfB));
	angleInBetween = angleInBetween * (180 / PI);
	return angleInBetween;
}

sf::Vector2f vectorRotateBy(sf::Vector2f t_vector, float t_angleRadians)
{
	float theAngle = t_angleRadians;
	sf::Vector2f usedVector = t_vector;
	sf::Vector2f rotation = sf::Vector2f{ usedVector.x, usedVector.y + (theAngle * 2) };
	return rotation;
}


sf::Vector2f vectorProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f projection = t_vector;
	sf::Vector2f projectTo = t_onto;
	float project = vectorDotProduct(projectTo, projection) / vectorLengthSquared(projection);
	sf::Vector2f vectorProj = sf::Vector2f(projectTo.x * project, projectTo.y * project);
	return vectorProj ;
}

sf::Vector2f vectorRejection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	sf::Vector2f rejection = t_vector - vectorProjection(t_vector, t_onto);
	return rejection;
}

float vectorScalarProjection(sf::Vector2f t_vector, sf::Vector2f t_onto)
{
	float scalarProject = vectorDotProduct(t_vector, t_onto);
	scalarProject = scalarProject / vectorLength(t_onto);
	return scalarProject;
}

sf::Vector2f vectorUnitVector(sf::Vector2f t_vector)
{
	sf::Vector2f unit{ 0.0f,0.0f };
	float length = vectorLength(t_vector);
	unit = sf::Vector2f{ t_vector.x / length , t_vector.y / length };
	return unit;
}

