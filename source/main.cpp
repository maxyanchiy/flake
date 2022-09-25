#include <cstdint>
#include <cstddef>
#include <cstdlib>

#include "LinearAllocator.h"
#include "ScopedStackAlloc.h"

struct Unit
{
	int hp{ 0 };
	int xp{ 0 };
};

class UnitSystem
{
public:
	explicit UnitSystem()
	{

	}

	~UnitSystem()
	{
		maxUnits = 155;
	}

	Unit* units{ nullptr };
	int maxUnits{ 0 };
};

int main()
{
	constexpr std::size_t m_allocationSize{ 8096 };
	flake::CLinearAllocator allocator{ m_allocationSize };
	UnitSystem* unitSystem = nullptr;
	{
		flake::CScopedStackAllocator scope{ allocator };
		unitSystem = scope.NewObject<UnitSystem>();
		unitSystem->maxUnits = 10;
	}

	return 0;
}