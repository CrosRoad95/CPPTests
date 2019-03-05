#include "StdInc.h"

ConvertableEnum::ConvertableEnum(SString strEnum)
{
	pGame->mEnums.insert({ strEnum, this });
};

void ConvertableEnum::InitializeEnums()
{
	ConvertableEnum* pEnum = new ConvertableEnum("Test");
	pEnum->Insert(Test::One, "One");
	pEnum->Insert(Test::Two, "Two");
	pEnum->Insert(Test::Three, "Three");

	Test output1;
	Test output2;
	Test output3;
	ConvertableEnum::Get<Test>(STRING_TO_ENUM, "Test", "One", output1);
	ConvertableEnum::Get<Test>(STRING_TO_ENUM, "Test", "Two", output2);
	ConvertableEnum::Get<Test>(STRING_TO_ENUM, "Test", "Three", output3);
	//printf("output %i %i %i\n", output1, output2, output3);
};

void ConvertableEnum::Insert(int e, SString str)
{
	emEnum.insert({ e, str });
};

template <typename T>
bool ConvertableEnum::Get(EType eType, SString strEnum, void* pInput, T &pOutput)
{
	switch (eType)
	{
	case STRING_TO_ENUM:
		ConvertableEnum* pEnum = pGame->mEnums.at(strEnum);
		if (pEnum == nullptr)
		{
			return false;
		}
		const char* strInput = reinterpret_cast<const char*>(pInput);

		for(auto mEnum : pEnum->emEnum)
		{
			if (strcmp(strInput, mEnum.second.c_str()) == 0)
			{
				pOutput = static_cast<T>(mEnum.first);
				return true;
			}
		}
		break;
	}

	return false;
};

template <typename T>
bool ConvertableEnum::Get(EType eType, SString strEnum, const char* pInput, T &pOutput)
{
	return ConvertableEnum::Get(eType, strEnum, static_cast<void*>(const_cast<char*>(pInput)), pOutput);
}