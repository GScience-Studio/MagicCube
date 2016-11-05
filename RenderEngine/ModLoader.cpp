
#include "ModLoader.h"

#include <fstream>

#undef _DEBUG

std::vector<double> loadOBJ(const char* FileName)
{
	std::string fullFileName = std::string("res\\modle\\") + FileName;

	std::vector<float> VerticesData;
	std::vector<float> NormalsData;
	std::vector<float> TextureData;

	std::vector<float> VerticesIndex;
	std::vector<float> NormalsIndex;
	std::vector<float> TextureIndex;

	char FirstWord[256];
	
	float GetData = 0;

	std::ifstream LoadOBJ(fullFileName);

	if (!LoadOBJ)
	{
		std::cout << "[ERROR]Unknow problem!Cannot open this file." << std::endl;
		
		return std::vector<double>();
	}

	LoadOBJ.setf(LoadOBJ.scientific);
	LoadOBJ.precision(4);

	while (!LoadOBJ.eof())
	{
		LoadOBJ >> FirstWord;

		if (FirstWord[0] == 'v' && FirstWord[1] == 0)
		{
#ifdef _DEBUG
			std::cout << "Find V	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				VerticesData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif

		}
		else if (FirstWord[0] == 'v' && FirstWord[1] == 'n')
		{
#ifdef _DEBUG
			std::cout << "Find VN	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				NormalsData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		else if (FirstWord[0] == 'v' && FirstWord[1] == 't')
		{
#ifdef _DEBUG
			std::cout << "Find VT	";
#endif

			for (int i = 0; i < 3; i++)
			{
				LoadOBJ >> GetData;
				TextureData.push_back(GetData);
#ifdef _DEBUG
				std::cout << i << ":" << GetData << " ";
#endif
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		else if (FirstWord[0] == 'f' && FirstWord[1] == 0)
		{
#ifdef _DEBUG
			std::cout << "Find F" << std::endl;
#endif
			for (int i = 0; i < 3; i++)
			{
				char GetDatas[33];

				char cGetVI[11];
				char cGetNI[11];
				char cGetTI[11];

				LoadOBJ >> GetDatas;

				int NowFindData = 0;
				int Position = 0;

				for (int i = 0; i < 32; i++)
				{
					if (GetDatas[i] == '/')
					{
						NowFindData++;
						Position = 0;
					}
					else if (GetDatas[i] == 0)
					{
						break;
					}
					else
					{
						if (NowFindData == 0)
						{
							cGetVI[Position] = GetDatas[i];
							cGetVI[Position + 1] = 0;
						}
						else if (NowFindData == 1)
						{
							cGetTI[Position] = GetDatas[i];
							cGetTI[Position + 1] = 0;
						}
						else if (NowFindData == 2)
						{
							cGetNI[Position] = GetDatas[i];
							cGetNI[Position + 1] = 0;
						}
						Position++;
					}
				}

				unsigned int GetVI = atoi(cGetVI);
				unsigned int GetNI = atoi(cGetNI);
				unsigned int GetTI = atoi(cGetTI);

#ifdef _DEBUG
				std::cout << "VI" << i << ":" << GetVI << " ";
#endif
				VerticesIndex.push_back(GetVI);

#ifdef _DEBUG
				std::cout << "NI" << i << ":" << GetTI << " ";
#endif
				TextureIndex.push_back(GetTI);

#ifdef _DEBUG
				std::cout << "TI" << i << ":" << GetNI << " ";
#endif
				NormalsIndex.push_back(GetNI);
			}
#ifdef _DEBUG
			std::cout << std::endl;
#endif
		}
		while (LoadOBJ.get() != 10 && !LoadOBJ.eof());
	}

	LoadOBJ.close();

	std::vector<float> VerticesTotal;
	std::vector<float> NormalsTotal;
	std::vector<float> TextureTotal;

	VerticesTotal.resize(VerticesIndex.size() * 3);
	NormalsTotal.resize(NormalsIndex.size() * 3);
	TextureTotal.resize(TextureIndex.size() * 3);

	for (unsigned int i = 0; i < VerticesIndex.size(); i++)
	{
		VerticesTotal[i * 3] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 3];
		VerticesTotal[i * 3 + 1] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 2];
		VerticesTotal[i * 3 + 2] = VerticesData[(unsigned int)VerticesIndex[i] * 3 - 1];

		if (TextureData.size() == 0)
		{
			TextureTotal[i * 3] = 0.0f;
			TextureTotal[i * 3 + 1] = 0.0f;
			TextureTotal[i * 3 + 2] = 0.0f;
		}
		else
		{
			TextureTotal[i * 3] = TextureData[(unsigned int)TextureIndex[i] * 3 - 3];
			TextureTotal[i * 3 + 1] = TextureData[(unsigned int)TextureIndex[i] * 3 - 2];
			TextureTotal[i * 3 + 2] = TextureData[(unsigned int)TextureIndex[i] * 3 - 1];
		}

		if (NormalsData.size() == 0)
		{
			NormalsTotal[i * 3] = 0.0f;
			NormalsTotal[i * 3 + 1] = 0.0f;
			NormalsTotal[i * 3 + 2] = 0.0f;
		}
		else
		{
			NormalsTotal[i * 3] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 3];
			NormalsTotal[i * 3 + 1] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 2];
			NormalsTotal[i * 3 + 2] = NormalsData[(unsigned int)NormalsIndex[i] * 3 - 1];
		}
	}
	std::vector<double> TotalData;

	TotalData.reserve(VerticesIndex.size() * 8);

	unsigned int vertex = 0;
	unsigned int texturePos = 0;

	for (unsigned int i = 0; i < VerticesIndex.size(); i++)
	{
		TotalData.push_back(VerticesTotal[vertex++]);
		TotalData.push_back(VerticesTotal[vertex++]);
		TotalData.push_back(VerticesTotal[vertex++]);

		TotalData.push_back(0.0f);
		TotalData.push_back(0.0f);
		TotalData.push_back(0.0f);

		TotalData.push_back(TextureTotal[texturePos++]);
		TotalData.push_back(TextureTotal[texturePos++]);
	}

	return TotalData;
}