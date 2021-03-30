#pragma once
#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include <random>
#include <cmath>
struct circle_t
{
	vec2	center = vec2(0);		// 2D position for translation
	float	radius = 1.0f;		// radius
	float	theta = 0.0f;			// rotation angle
	vec4	color;				// RGBA color in [0,1]
	vec2	moveDir;
	uint	id;
	mat4	model_matrix;		// modeling transformation
	// public functions
	void	update(float t);
};

inline std::vector<circle_t> create_circles(float n)
{
	std::vector<circle_t> circles;
	circles.clear();
	circle_t c;
	// 이부분에서 넣는 갯수만큼 원 들어감
	// center : ( -16/9 ~ 16/9 , -1 ~ 1)
	// Radius : 원갯수 제곱에 반비례
	// theta = 0.0f 고정
	// 그럼 그릴 원 갯수를 받아서 for문으로 하자

	//c = { vec2(0,1),0.285029f,0.0f,vec4(1.0f,0.5f,0.5f,1.0f) };
	//circles.emplace_back(c);
	srand(GetTickCount());
	for (int i = 0; i < n; i++)
	{
		float r, x, y;
		r = ((float)rand() / float(RAND_MAX) + 1) / (3 * sqrt(n));
		x = ((32.0f / 9 - 2 * r) * (float)rand() / float(RAND_MAX)) - 16.0f / 9 + r;
		y = ((2 - 2 * r) * (float)rand() / float(RAND_MAX)) - 1 + r;
		bool is_pos_okay = false;
		if (i != 0)
		{
			while (!is_pos_okay)
			{
				is_pos_okay = true;
				r = ((float)rand() / float(RAND_MAX) + 1) / (3 * sqrt(n));
				x = ((32.0f / 9 - 2 * r) * (float)rand() / float(RAND_MAX)) - 16.0f / 9 + r;
				y = ((2.0f - 2 * r) * (float)rand() / float(RAND_MAX)) - 1 + r;
				if (x <= r - 16.0f / 9 || x >= 16.0f / 9 - r || y <= r - 1 || y >= 1 - r)
				{
					is_pos_okay = false;
					continue;
				}
				for (unsigned int j = 0; j < circles.size(); j++)
				{
					if ((circles[j].center.x - x) * (circles[j].center.x - x) + (circles[j].center.y - y) * (circles[j].center.y - y) < (r + circles[j].radius) * (r + circles[j].radius))
					{ // do loop again
						is_pos_okay = false;
					}
				}
			}
		}
		//c = { vec2(x,y),r,0.0f,vec4((float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX)) };
		float x_vel = (float)rand() / float(RAND_MAX) * 5 - 2.5f;
		float y_vel = (float)rand() / float(RAND_MAX) * 5 - 2.5f;
		//printf("%d: x: %f y: %f r: %f xvel: %f yvel: %f\n", i, x, y, r, x_vel, y_vel);
		//printf("%d: %f %f\n", i, x_vel, y_vel);
		c = { vec2(x,y),r,0.0f,vec4((float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX),(float)rand() / float(RAND_MAX))/*vec4(i / n,i / n,i / n,i / n)*/,vec2(x_vel,y_vel),circles.size() };
		circles.emplace_back(c);
	}
	return circles;
}

inline void circle_t::update(float t)
{
	// 여기에 움직이는거 넣어야하는건가?
	// these transformations will be explained in later transformation lecture
	if (moveDir.x > 7.0f)
		moveDir.x = 7.0f;
	if (moveDir.y > 7.0f)
		moveDir.y = 7.0f;
	mat4 scale_matrix =
	{
		radius, 0, 0, 0,
		0, radius, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	mat4 translate_matrix =
	{
		1, 0, 0, center.x,
		0, 1, 0, center.y,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	center.x += moveDir.x * t;
	center.y += moveDir.y * t;

	model_matrix = translate_matrix * scale_matrix;
	if (center.x < radius - 16.0f / 9) // left
	{
		center.x = radius - 16.0f / 9;
		if (moveDir.x < 0)
			moveDir.x = -moveDir.x;
	}
	else if (center.x > 16.0f / 9 - radius) // right
	{
		center.x = 16.0f / 9 - radius;
		if (moveDir.x > 0)
			moveDir.x = -moveDir.x;

	}
	if (center.y < radius - 1) // up
	{
		center.y = radius - 1;
		if (moveDir.y < 0)
			moveDir.y = -moveDir.y;
	}
	else if (center.y > 1 - radius) // down
	{
		center.y = 1 - radius;
		if (moveDir.y > 0)
			moveDir.y = -moveDir.y;
	}
}

#endif
