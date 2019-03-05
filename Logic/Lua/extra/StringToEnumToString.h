#pragma once

enum EType {
	STRING_TO_ENUM
};

enum Test {
	One,
	Two,
	Three,
};

class ConvertableEnum
{
public:
	ConvertableEnum(SString strEnum);
	static void InitializeEnums();

	void Insert(int e, SString str);

	template <typename T>
	static bool Get(EType eType, SString strEnum, void* pInput, T &pOutput);
	template <typename T>
	static bool Get(EType eType, SString strEnum, const char* pInput, T &pOutput);

	std::map<int, SString> emEnum;
private:

};
