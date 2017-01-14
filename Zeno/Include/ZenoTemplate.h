#pragma once

template <class T>
class Global : public MemoryObject
{
public:
	inline static T* getInst()
	{
		if (!s_pInst)
		{
			s_pInst = ZENO_NEW T;
		}

		return s_pInst;
	}

	inline ~Global() { }

private:
	static T* s_pInst;

	inline Global() { }

	Global(const Global& rSource);

	Global& operator=(const Global& rSource);

};
