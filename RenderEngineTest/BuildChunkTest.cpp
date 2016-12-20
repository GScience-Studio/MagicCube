
#include <math.h>
#include "../ChunkUniversal.h"

int seed = 1000000;

double persistence = 1.4f;

int Number_Of_Octaves = 3;



double PerlinNoise_2D(unsigned int X, unsigned int Y);



double Noise1(unsigned int x, unsigned int y)

{

	if (seed < 0)

	{

		seed = -seed;

	}

	int n = x + y * 57;

	n = n + ((n + seed)*n - seed) * seed;

	n = (n << 13) ^ n;

	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);

}



double SmoothNoise_1(unsigned int x, unsigned int y)

{

	double corners = (Noise1(x - 1, y - 1) + Noise1(x + 1, y - 1) + Noise1(x - 1, y + 1) + Noise1(x + 1, y + 1)) / 16.0f;

	double sides = (Noise1(x - 1, y) + Noise1(x + 1, y) + Noise1(x, y - 1) + Noise1(x, y + 1)) / 8.0f;

	double center = Noise1(x, y) / 4.0f;

	return corners + sides + center;

}



double Cosine_Interpolate(double a, double b, double x)

{

	double ft = x * 3.1415927;

	double f = (1 - cos(ft)) * 0.5f;



	return  a*(1 - f) + b*f;



}



double InterpolatedNoise_1(double x, double y)

{



	int integer_X = int(x);

	double fractional_X = x - integer_X;



	int integer_Y = int(y);

	double fractional_Y = y - integer_Y;



	double v1 = SmoothNoise_1(integer_X, integer_Y);

	double v2 = SmoothNoise_1(integer_X + 1, integer_Y);

	double v3 = SmoothNoise_1(integer_X, integer_Y + 1);

	double v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);



	double i1 = Cosine_Interpolate(v1, v2, fractional_X);

	double i2 = Cosine_Interpolate(v3, v4, fractional_X);



	return Cosine_Interpolate(i1, i2, fractional_Y);

}



double PerlinNoise_2D(int X, int Y)

{

	double x = (X + 2147483648) / 50.0;

	double y = (Y + 2147483648) / 50.0;



	double total = 0.0f;

	double p = persistence;

	int n = Number_Of_Octaves - 1;



	for (int i = 0; i <= n; i++)

	{

		double frequency = pow((double)2, i);

		double amplitude = pow(p, i);



		total = total + InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;

	}



	return total;

}



//临时地形算法结束



void buildMap(int chunkX,int chunkZ,unsigned int* chunkData)

{

	//不用加锁

	for (int i = 0; i < 16; i++)

	{

		for (int j = 0; j < 16; j++)

		{

			bool HasSetGrass = false;



			int m = (PerlinNoise_2D(chunkX * 16 + i, chunkZ * 16 + j) * 5.0 + 10) * 5.0;



			if (m > 256)

				m = 256;

			m /= 16;

			for (int m3 = m + 1; m3 < 16; m3++)

			{

				chunkData[blockChunkLocationToShort(i, m3, j)] = 0;

			}

			for (int m2 = m; m2 > 0; m2--)

			{

				if (!HasSetGrass)

				{

					chunkData[blockChunkLocationToShort(i, m2, j)] = 1;

					HasSetGrass = true;

				}

				else

				{

					chunkData[blockChunkLocationToShort(i, m2, j)] = 1;

				}

			}

		}

	}

}