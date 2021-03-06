// Collision Detection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::cout;
inline float calc_mag(std::vector<float> vec)
{
	return (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1])));
}
inline float dot(std::vector<float> a, std::vector<float> b)
{
	return a[0] * b[0] + a[1] * b[1];
}
class shape
{
	std::vector <float> point = { 0,0 };
	float center[2];
public:
	std::vector <std::vector <float>> vertex;
	std::vector < std::vector <float>> side;
	shape(float x, float y)
	{
		center[0] = x;
		center[1] = y;
	}
	void add_vertex(float x, float y)
	{
		point[0] = x;
		point[1] = y;
		vertex.push_back(point);
	}
	void make_side()
	{
		for (int i = 0; i != (vertex.size() - 1); i++)
		{
			std::vector <float> vec;
			vec.push_back(vertex[i + 1][0] - vertex[i][0]);
			vec.push_back(vertex[i + 1][1] - vertex[i][1]);
			side.push_back(vec);
		}
		{
			int  i = vertex.size() - 1;
			std::vector <float> vec;
			vec.push_back(vertex[0][0] - vertex[i][0]);
			vec.push_back(vertex[0][1] - vertex[i][1]);
			side.push_back(vec);
		}
	}
	inline int NoOfVertex() { return vertex.size(); }
	void disp()
	{
		for (int i = 0; i != side.size(); i++)
		{
			std::cout << "(" << side[i][0] << "," << side[i][1] << ")" << std::endl;
		}
	}

};

inline std::vector<float> normalize(const std::vector<float>& vec)
{
	std::vector<float> ret_vect;
	float mag = calc_mag(vec);
	/*ret_vect.push_back(vec[0] / mag);
	ret_vect.push_back(vec[1] / mag);*/
	ret_vect.push_back(vec[0] / mag);
	ret_vect.push_back(vec[1] / mag);
	return ret_vect;

}

inline std::vector <float> normal(const std::vector <float> & vec)
{
	return std::vector<float>{vec[1], -vec[0]};
}

bool overlap(shape shape1, shape shape2)
{
	bool result = true;
	/*To check for overlap in axis from 1st object*/
	for (int j = 0; j != shape1.NoOfVertex(); j++)
	{
		float shape1_max, shape2_max, shape1_min, shape2_min;
		std::vector <float> axis(2);
		axis = normal(shape1.side[j]);
		axis = normalize(axis);
		//std::cout << "Axis: (" << axis[0] << "," << axis[1] << ")" << std::endl;
		shape1_max = dot(shape1.vertex[0], axis);
		shape1_min = shape1_max;
		shape2_max = dot(shape2.vertex[0], axis);
		shape2_min = shape2_max;
		for (int i = 0; i != shape1.NoOfVertex(); i++)
		{
			float dot_prod1;
			dot_prod1 = dot(shape1.vertex[i], axis);
			//std::cout << dot_prod1 << ":";
			if (shape1_max < dot_prod1) { shape1_max = dot_prod1; }
			if (shape1_min > dot_prod1) { shape1_min = dot_prod1; }
		}
		for (int i = 0; i != shape2.NoOfVertex(); i++)
		{
			float dot_prod2;
			dot_prod2 = dot(shape2.vertex[i], axis);
			if (shape2_max < dot_prod2) { shape2_max = dot_prod2; }
			if (shape2_min > dot_prod2) { shape2_min = dot_prod2; }

		}
		if (shape1_max < shape2_min || shape1_min > shape2_max)
		{
			return false;;
		}
	}
	/*To check for overlapping in axis from 2nd object*/
	for (int j = 0; j != shape2.NoOfVertex(); j++)
	{
		float shape1_max, shape2_max, shape1_min, shape2_min;
		std::vector <float> axis(2);
		axis = normal(shape2.side[j]);
		axis = normalize(axis);
		//std::cout << "Axis: (" << axis[0] << "," << axis[1] << ")" << std::endl;
		shape1_max = dot(shape1.vertex[0], axis);
		shape1_min = shape1_max;
		shape2_max = dot(shape2.vertex[0], axis);
		shape2_min = shape2_max;
		for (int i = 0; i != shape1.NoOfVertex(); i++)
		{
			float dot_prod1;
			dot_prod1 = dot(shape1.vertex[i], axis);
			//std::cout << dot_prod1 << ":";
			if (shape1_max < dot_prod1) { shape1_max = dot_prod1; }
			if (shape1_min > dot_prod1) { shape1_min = dot_prod1; }
		}
		for (int i = 0; i != shape2.NoOfVertex(); i++)
		{
			float dot_prod2;
			dot_prod2 = dot(shape2.vertex[i], axis);
			if (shape2_max < dot_prod2) { shape2_max = dot_prod2; }
			if (shape2_min > dot_prod2) { shape2_min = dot_prod2; }

		}
		if (shape1_max < shape2_min || shape1_min > shape2_max)
		{
			return false;
		}


		//std::cout << std::endl;
		//std::cout << "Min: " << shape1_min << "   Max: " << shape1_max << std::endl;
		//std::cout << "2Min: " << shape2_min << " Max: " << shape2_max << std::endl;

	}
	return result;
}
int main()
{
	shape shape1(2, 2);
	shape1.add_vertex(-4, -3);
	shape1.add_vertex(-6, -3);
	shape1.add_vertex(-4, -1);
	shape1.add_vertex(-3, -2);
	shape1.make_side();

	shape shape2(4, 3);
	shape2.add_vertex(-3, -1);
	shape2.add_vertex(-1, -1);
	shape2.add_vertex(-1, -2);
	shape2.add_vertex(-2, -3);
	//shape2.add_vertex(-4, -2);
	//shape2.add_vertex(-1, -2);
	shape2.make_side();
	/*vector <float> test{ 4,5 };
	vector <float> result(2);
	result = normal(test);
	cout << "Normal: (" << result[0] << "," << result[1] << std::endl;
	result = normalize(test);
	cout << "Normalized: (" << result[0] << "," << result[1] << std::endl;
	*/
	std::cout << std::endl << "Final: " << overlap(shape1, shape2);
}



