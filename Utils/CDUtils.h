#pragma once
class CDUtils
{
public:
	CDUtils(void);
	~CDUtils(void);

	static int GetMultiIndexOfSubsystem(int x, int y, int subsystemWidth, int subsystemHeight, int countOfColumns)
	{
		return x / subsystemWidth + countOfColumns * y /subsystemHeight; 
	}
	
	static void GetCountOfRowsAndColumnsForParticlesCount(int *countOfRows, int *countOfColumns, int countOfParticles)
	{
		// TODO: need to implement
	}
};

